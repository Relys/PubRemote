#include "receiver.h"
#include "esp_log.h"
#include "esp_now.h"
#include "esp_timer.h"
#include "esp_wifi.h"
#include "peers.h"
#include "powermanagement.h"
#include "time.h"
#include <string.h>
#include <ui/ui.h>

static const char *TAG = "PUBMOTE-RECEIVER";

#define TIMEOUT_DURATION_MS 10000     // 10 seconds
#define RECONNECTING_DURATION_MS 1000 // 1 seconds

esp_timer_handle_t connection_timeout_timer;
esp_timer_handle_t reconnecting_timer;
int pairing_state = 0;
int32_t secret_code = 0;
uint8_t remote_addr[6] = {0, 0, 0, 0, 0, 0};

static void connection_timeout_callback(void *arg) {
  lv_label_set_text(ui_ConnectionState, "Disconnected");
}

static void reconnecting_timer_callback(void *arg) {
  lv_label_set_text(ui_ConnectionState, "Reconnecting");
  esp_timer_start_once(connection_timeout_timer, TIMEOUT_DURATION_MS * 1000);
}

static void on_data_recv(const uint8_t *mac_addr, const uint8_t *data, int len) {
  ESP_LOGI(TAG, "RECEIVED");
  int64_t deltaTime = get_current_time_ms() - LAST_COMMAND_TIME;
  LAST_COMMAND_TIME = 0;
  ESP_LOGI(TAG, "RTT: %lld", deltaTime);

  if (pairing_state == 1 && len == 6) {
    memcpy(remote_addr, data, 6);
    ESP_LOGI(TAG, "Got Pairing request from VESC Express");
    ESP_LOGI(TAG, "packet Length: %d", len);
    ESP_LOGI(TAG, "MAC Address: %02X:%02X:%02X:%02X:%02X:%02X", data[0], data[1], data[2], data[3], data[4], data[5]);
    // ESP_LOGI(TAG, "Incorrect MAC Address: %02X:%02X:%02X:%02X:%02X:%02X", mac_addr[0], mac_addr[1], mac_addr[2],
    //          mac_addr[3], mac_addr[4], mac_addr[5]);
    uint8_t TEST[1] = {420};
    esp_now_peer_info_t peerInfo = {};
    // uint8_t PEER_MAC_ADDRESS_BROADCAST[6] = {255, 255, 255, 255, 255, 255};
    peerInfo.channel = 1; // Set the channel number (0-14)
    peerInfo.encrypt = false;
    memcpy(peerInfo.peer_addr, remote_addr, sizeof(remote_addr));
    // ESP_ERROR_CHECK(esp_now_add_peer(&peerInfo));
    if (!esp_now_is_peer_exist(&peerInfo)) {
      esp_now_add_peer(&peerInfo);
    }

    esp_err_t result = esp_now_send(&remote_addr, (uint8_t *)&TEST, sizeof(TEST));
    if (result != ESP_OK) {
      // Handle error if needed
      ESP_LOGE(TAG, "Error sending data: %d", result);
    }
    else {
      ESP_LOGI(TAG, "Sent response back to VESC Express");
      pairing_state++;
    }
  }
  else if (pairing_state == 2 && len == 4) {
    // grab secret code
    ESP_LOGI(TAG, "Grabbing secret code");
    ESP_LOGI(TAG, "packet Length: %d", len);
    secret_code = (int32_t)(data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    ESP_LOGI(TAG, "Secret Code: %li", secret_code);
    pairing_state = 0;
  }

  if (pairing_state == 0 && len == 32) {
    // Reset the timers
    esp_timer_stop(connection_timeout_timer);
    esp_timer_stop(reconnecting_timer);
    start_or_reset_deep_sleep_timer(DEEP_SLEEP_DELAY_MS);
    lv_label_set_text(ui_ConnectionState, "Connected");
    // Restart the connection timeout timer
    esp_timer_start_once(reconnecting_timer, RECONNECTING_DURATION_MS * 1000);
    uint8_t mode = data[0];
    uint8_t fault_code = data[1];
    float pitch_angle = (int16_t)((data[2] << 8) | data[3]) / 10.0;
    float roll_angle = (int16_t)((data[4] << 8) | data[5]) / 10.0;
    uint8_t state = data[6];
    uint8_t switch_state = data[7];
    float input_voltage_filtered = (int16_t)((data[8] << 8) | data[9]) / 10.0;
    int16_t rpm = (int16_t)((data[10] << 8) | data[11]);
    float speed = (int16_t)((data[12] << 8) | data[13]) / 10.0;
    float tot_current = (int16_t)((data[14] << 8) | data[15]) / 10.0;
    float duty_cycle_now = (float)data[16] / 100.0 - 0.5;
    float distance_abs;
    memcpy(&distance_abs, &data[17], sizeof(float));
    float fet_temp_filtered = (float)data[21] / 2.0;
    float motor_temp_filtered = (float)data[22] / 2.0;
    uint32_t odometer = (uint32_t)((data[23] << 24) | (data[24] << 16) | (data[25] << 8) | data[26]);
    float battery_level = (float)data[27] / 2.0;
    int32_t super_secret_code = (int32_t)((data[28] << 24) | (data[29] << 16) | (data[30] << 8) | data[31]);

    switch (switch_state) {
    case 0:
      lv_arc_set_value(ui_LeftSensor, 0);
      lv_arc_set_value(ui_RightSensor, 0);
      break;
    case 1:
      lv_arc_set_value(ui_LeftSensor, 1);
      lv_arc_set_value(ui_RightSensor, 0);
      break;
    case 2:
      lv_arc_set_value(ui_LeftSensor, 0);
      lv_arc_set_value(ui_RightSensor, 1);
      break;
    case 3:
      lv_arc_set_value(ui_LeftSensor, 1);
      lv_arc_set_value(ui_RightSensor, 1);
      break;
    default:
      break;
    }

    char *formattedString;
    asprintf(&formattedString, "%.0f%%", battery_level);
    lv_label_set_text(ui_BatteryDisplay, formattedString);
    asprintf(&formattedString, "Mot: %.0fC | Cont: %.0fC", motor_temp_filtered, fet_temp_filtered);
    lv_label_set_text(ui_TempStats, formattedString);
    asprintf(&formattedString, "Trip: %.0fkm | Rem: -69km", distance_abs);
    lv_label_set_text(ui_DistanceStats, formattedString);
    asprintf(&formattedString, "%.1f", speed);
    lv_label_set_text(ui_PrimaryStat, formattedString);
    free(formattedString);
    lv_arc_set_value(ui_DutyCycle, duty_cycle_now);
    // Print the extracted values
    // ESP_LOGI(TAG, "Mode: %d", mode);
    // ESP_LOGI(TAG, "Fault Code: %d", fault_code);
    // ESP_LOGI(TAG, "Pitch Angle: %.1f", pitch_angle);
    // ESP_LOGI(TAG, "Roll Angle: %.1f", roll_angle);
    // ESP_LOGI(TAG, "State: %d", state);
    // ESP_LOGI(TAG, "Switch State: %d", switch_state);
    // ESP_LOGI(TAG, "Input Voltage Filtered: %.1f", input_voltage_filtered);
    // ESP_LOGI(TAG, "RPM: %d", rpm);
    // ESP_LOGI(TAG, "Speed: %.1f", speed);
    // ESP_LOGI(TAG, "Total Current: %.1f", tot_current);
    // ESP_LOGI(TAG, "Duty Cycle Now: %.2f", duty_cycle_now);
    // ESP_LOGI(TAG, "Distance Absolute: %.2f", distance_abs);
    // ESP_LOGI(TAG, "FET Temperature Filtered: %.1f", fet_temp_filtered);
    // ESP_LOGI(TAG, "Motor Temperature Filtered: %.1f", motor_temp_filtered);
    // ESP_LOGI(TAG, "Odometer: %lu", odometer);
    // ESP_LOGI(TAG, "Battery Level: %.1f", battery_level);
  }
  else {
    ESP_LOGI(TAG, "Invalid data length");
  }
}

void init_receiver() {
  ESP_LOGI(TAG, "Registered RX callback");
  ESP_ERROR_CHECK(esp_now_register_recv_cb(on_data_recv));

  esp_timer_create_args_t connection_timeout_args = {.callback = connection_timeout_callback,
                                                     .arg = NULL,
                                                     .dispatch_method = ESP_TIMER_TASK,
                                                     .name = "ConnectionTimeoutTimer"};
  ESP_ERROR_CHECK(esp_timer_create(&connection_timeout_args, &connection_timeout_timer));
  esp_timer_create_args_t reconnecting_timer_args = {.callback = reconnecting_timer_callback,
                                                     .arg = NULL,
                                                     .dispatch_method = ESP_TIMER_TASK,
                                                     .name = "ReconnectingTimer"};
  ESP_ERROR_CHECK(esp_timer_create(&reconnecting_timer_args, &reconnecting_timer));
}