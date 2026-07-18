#include QMK_KEYBOARD_H
enum app_states {
    STATE_MENU,
    STATE_TIMER,
    STATE_GAME,
    STATE_EDIT TIME,
    STATE_DATE,
    STATE_EDIT DATE,
};
static uint8_t current_state = STATE_MENU;
enum menu_options {
    MENU_TIMER,
    MENU_GAME,
    MENU_DATE,
    MENU_TOTAL
};
static uint8_t menu_cursor = MENU_TIMER;
[0] = LAYOUT_direct(
    KC_A, KC_B,   //
    KC_C, KC_D,   // 
    KC_E, KC_F    // 
)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // --- 情況 1：如果你目前處於「主選單 (STATE_MENU)」---
        if (current_state == STATE_MENU) {
            // 假設我們把「第 5 粒掣 (KC_E)」定義為【確認進入】
            if (keycode == KC_E) { 
                // 睇吓你個選單游標停喺邊，就跳去邊個狀態
                if (menu_cursor == MENU_TIMER) {
                    current_state = STATE_TIMER;
                } else if (menu_cursor == MENU_GAME) {
                    current_state = STATE_GAME;
                } else if (menu_cursor == MENU_DATE) {
                    current_state = STATE_DATE;
                }
                return false; // 阻截原本的 KC_E 鍵位，唔好發射 "E" 字去電腦
            }
        }
        
        // --- 情況 2：如果你處於「計時器 (STATE_TIMER)」---
        else if (current_state == STATE_TIMER) {
            // 收到貨後，喺度寫計時器模式下，5粒掣分別做咩
            // 例如：撳 KC_A 等於開始/暫停
            
            // 記得要設一粒掣（例如旋鈕撳落去）可以【返回主選單】
            if (keycode == KC_F) { 
                current_state = STATE_MENU; 
                return false; 
            }
        }
        
        // --- 情況 3：如果你處於「遊戲 (STATE_GAME)」---
        else if (current_state == STATE_GAME) {
            // 收到貨後，喺度寫遊戲模式下，5粒掣分別做咩
            // 例如：KC_A, KC_B, KC_C 變成左、下、右
            
            if (keycode == KC_F) { current_state = STATE_MENU; return false; }
        }
    }
    return true;
}
