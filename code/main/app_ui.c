#include "app_ui.h"
#include "audio_player.h"
#include "esp32_s3_szp.h"
#include "file_iterator.h"
#include "string.h"
#include <dirent.h>

static const char *TAG = "app_ui";

static audio_player_config_t player_config = {0};
static uint8_t g_sys_volume = VOLUME_DEFAULT;
static file_iterator_instance_t *file_iterator = NULL;

lv_obj_t *music_list;
lv_obj_t *label_play_pause;
lv_obj_t *btn_play_pause;
lv_obj_t *volume_slider;

// 播放指定序号的音乐
static void play_index(int index)
{
    ESP_LOGI(TAG, "play_index(%d)", index);

    char filename[128];
    int retval = file_iterator_get_full_path_from_index(file_iterator, index, filename, sizeof(filename));
    if (retval == 0)
    {
        ESP_LOGE(TAG, "unable to retrieve filename");
        return;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp)
    {
        ESP_LOGI(TAG, "Playing '%s'", filename);
        audio_player_play(fp);
    }
    else
    {
        ESP_LOGE(TAG, "unable to open index %d, filename '%s'", index, filename);
    }
}

// 设置声音处理函数
static esp_err_t _audio_player_mute_fn(AUDIO_PLAYER_MUTE_SETTING setting)
{
    esp_err_t ret = ESP_OK;
    // 获取当前音量
    // uint8_t volume = get_sys_volume();
    // 判断是否需要静音
    bsp_codec_mute_set(setting == AUDIO_PLAYER_MUTE ? true : false);
    // 如果不是静音 设置音量
    if (setting == AUDIO_PLAYER_UNMUTE)
    {
        bsp_codec_volume_set(g_sys_volume, NULL);
    }
    ret = ESP_OK;

    return ret;
}

// 播放音乐函数 播放音乐的时候 会不断进入
static esp_err_t _audio_player_write_fn(void *audio_buffer, size_t len, size_t *bytes_written, uint32_t timeout_ms)
{
    return bsp_i2s_write(audio_buffer, len, bytes_written, timeout_ms);
}

// 设置采样率 播放的时候进入一次
static esp_err_t _audio_player_std_clock(uint32_t rate, uint32_t bits_cfg, i2s_slot_mode_t ch)
{
    esp_err_t ret = ESP_OK;
    // ret = bsp_speaker_set_fs(rate, bits_cfg, ch);
    // ret = bsp_codec_set_fs(rate, bits_cfg, ch);
    return ret;
}

// 回调函数 播放器每次动作都会进入
static void _audio_player_callback(audio_player_cb_ctx_t *ctx)
{
    ESP_LOGI(TAG, "ctx->audio_event = %d", ctx->audio_event);
    switch (ctx->audio_event)
    {
    case AUDIO_PLAYER_CALLBACK_EVENT_IDLE:
    { // 播放完一首歌 进入这个case
        ESP_LOGI(TAG, "AUDIO_PLAYER_REQUEST_IDLE");
        // 指向下一首歌
        file_iterator_next(file_iterator);
        int index = file_iterator_get_index(file_iterator);
        ESP_LOGI(TAG, "playing index '%d'", index);
        play_index(index);
        // 修改当前播放的音乐名称
        lvgl_port_lock(0);
        lv_dropdown_set_selected(music_list, index);
        lv_obj_t *label_title = (lv_obj_t *)music_list->user_data;
        lv_label_set_text_static(label_title, file_iterator_get_name_from_index(file_iterator, index));
        lvgl_port_unlock();
        break;
    }
    case AUDIO_PLAYER_CALLBACK_EVENT_PLAYING: // 正在播放音乐
        ESP_LOGI(TAG, "AUDIO_PLAYER_REQUEST_PLAY");
        pa_en(1); // 打开音频功放
        break;
    case AUDIO_PLAYER_CALLBACK_EVENT_PAUSE: // 正在暂停音乐
        ESP_LOGI(TAG, "AUDIO_PLAYER_REQUEST_PAUSE");
        pa_en(0); // 关闭音频功放
        break;
    default:
        break;
    }
}

// mp3播放器初始化
void mp3_player_init(lv_ui *ui)
{
    // 获取文件信息
    file_iterator = file_iterator_new(MUSIC_BASE); // 从SD卡获取音乐文件
    assert(file_iterator != NULL);

    // 初始化音频播放
    player_config.mute_fn = _audio_player_mute_fn;
    player_config.write_fn = _audio_player_write_fn;
    player_config.clk_set_fn = _audio_player_std_clock;
    player_config.priority = 6;
    player_config.coreID = 1;

    ESP_ERROR_CHECK(audio_player_new(player_config));
    ESP_ERROR_CHECK(audio_player_callback_register(_audio_player_callback, NULL));

    // 显示界面
    gui_guider_ui(ui);
}

// 播放暂停按钮 事件处理函数
static void btn_play_pause_cb(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event);
    lv_obj_t *lab = (lv_obj_t *)btn->user_data;

    audio_player_state_t state = audio_player_get_state();
    printf("state=%d\n", state);
    if (state == AUDIO_PLAYER_STATE_IDLE)
    {
        lvgl_port_lock(0);
        lv_label_set_text_static(lab, LV_SYMBOL_PAUSE);
        lvgl_port_unlock();
        int index = file_iterator_get_index(file_iterator);
        ESP_LOGI(TAG, "playing index '%d'", index);
        play_index(index);
    }
    else if (state == AUDIO_PLAYER_STATE_PAUSE)
    {
        lvgl_port_lock(0);
        lv_label_set_text_static(lab, LV_SYMBOL_PAUSE);
        lvgl_port_unlock();
        audio_player_resume();
    }
    else if (state == AUDIO_PLAYER_STATE_PLAYING)
    {
        lvgl_port_lock(0);
        lv_label_set_text_static(lab, LV_SYMBOL_PLAY);
        lvgl_port_unlock();
        audio_player_pause();
    }
}

// 上一首 下一首 按键事件处理函数
static void prev_next_music(bool is_next)
{
    if (is_next)
    {
        file_iterator_next(file_iterator);
    }
    else
    {
        file_iterator_prev(file_iterator);
    }
    // 修改当前的音乐名称
    int index = file_iterator_get_index(file_iterator);
    lvgl_port_lock(0);
    lv_dropdown_set_selected(music_list, index);
    lv_obj_t *label_title = (lv_obj_t *)music_list->user_data;
    lv_label_set_text_static(label_title, file_iterator_get_name_from_index(file_iterator, index));
    lvgl_port_unlock();
    // 执行音乐事件
    audio_player_state_t state = audio_player_get_state();
    printf("prev_next_state=%d\n", state);
    if (state == AUDIO_PLAYER_STATE_IDLE)
    {
        // Nothing to do
    }
    else if (state == AUDIO_PLAYER_STATE_PAUSE)
    { // 如果当前正在暂停歌曲
        play_index(index);
        audio_player_pause();
    }
    else if (state == AUDIO_PLAYER_STATE_PLAYING)
    { // 如果当前正在播放歌曲
        // 播放歌曲
        play_index(index);
    }
}
static void btn_prev_next_cb(lv_event_t *event)
{
    bool is_next = (bool)event->user_data;
    prev_next_music(is_next);
}

// 音量调节滑动条 事件处理函数
static void volume_slider_cb(lv_event_t *event)
{
    lv_obj_t *slider = lv_event_get_target(event);
    int volume = lv_slider_get_value(slider); // 获取slider的值
    bsp_codec_volume_set(volume, NULL);       // 设置声音大小
    g_sys_volume = volume;                    // 把声音赋值给g_sys_volume保存
    ESP_LOGI(TAG, "volume '%d'", volume);
}

// 音乐列表 点击事件处理函数
static void music_list_cb(lv_event_t *event)
{
    lv_obj_t *label_title = (lv_obj_t *)music_list->user_data;

    uint16_t index = lv_dropdown_get_selected(music_list);
    ESP_LOGI(TAG, "switching index to '%d'", index);
    file_iterator_set_index(file_iterator, index);
    lvgl_port_lock(0);
    lv_label_set_text_static(label_title, file_iterator_get_name_from_index(file_iterator, index));
    lvgl_port_unlock();

    audio_player_state_t state = audio_player_get_state();
    if (state == AUDIO_PLAYER_STATE_PAUSE)
    { // 如果当前正在暂停歌曲
        play_index(index);
        audio_player_pause();
    }
    else if (state == AUDIO_PLAYER_STATE_PLAYING)
    { // 如果当前正在播放歌曲
        play_index(index);
    }
}

// 音乐名称加入列表
static void build_file_list(lv_obj_t *music_list)
{
    lv_obj_t *label_title = (lv_obj_t *)music_list->user_data;

    lvgl_port_lock(0);
    lv_dropdown_clear_options(music_list);
    lvgl_port_unlock();

    for (size_t i = 0; i < file_iterator->count; i++)
    {
        const char *file_name = file_iterator_get_name_from_index(file_iterator, i);
        if (NULL != file_name)
        {
            lvgl_port_lock(0);
            lv_dropdown_add_option(music_list, file_name, i); // 添加音乐名称到列表中
            lvgl_port_unlock();
        }
    }
    lvgl_port_lock(0);
    lv_dropdown_set_selected(music_list, 0);                                                    // 选择列表中的第一个
    lv_label_set_text_static(label_title, file_iterator_get_name_from_index(file_iterator, 0)); // 显示list中第一个音乐的名称
    lvgl_port_unlock();
}

// 播放器界面初始化
void gui_guider_ui(lv_ui *ui)
{
    lvgl_port_lock(0);

    music_list = ui->screen_music_list;
    label_play_pause = ui->screen_stop_bt_label;
    btn_play_pause = ui->screen_stop_bt;
    volume_slider = ui->screen_volume;

    /* 创建播放暂停控制按键 */
    lv_obj_set_user_data(ui->screen_stop_bt, (void *)ui->screen_stop_bt_label);
    lv_obj_add_event_cb(ui->screen_stop_bt, btn_play_pause_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* 创建上一首控制按键 */
    lv_obj_set_user_data(ui->screen_pre_bt, (void *)ui->screen_pre_bt_label);
    lv_obj_add_event_cb(ui->screen_pre_bt, btn_prev_next_cb, LV_EVENT_CLICKED, (void *)false);

    /* 创建下一首控制按键 */
    lv_obj_set_user_data(ui->screen_next_bt, (void *)ui->screen_next_bt_label);
    lv_obj_add_event_cb(ui->screen_next_bt, btn_prev_next_cb, LV_EVENT_CLICKED, (void *)true);

    /* 创建声音调节滑动条 */
    lv_obj_add_event_cb(ui->screen_volume, volume_slider_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* 创建音乐标题 */
    lv_obj_set_user_data(ui->screen_music_name, (void *)ui->screen_stop_bt);

    /* 创建音乐列表 */
    lv_dropdown_clear_options(ui->screen_music_list);
    lv_obj_set_user_data(ui->screen_music_list, (void *)ui->screen_music_name);
    lv_obj_add_event_cb(ui->screen_music_list, music_list_cb, LV_EVENT_VALUE_CHANGED, NULL);

    build_file_list(ui->screen_music_list);

    lvgl_port_unlock();
}

// AI人动画
LV_IMG_DECLARE(img_bilibili120);

lv_obj_t *gif_start;

// AI人出现在屏幕
void ai_gui_in(void)
{
    lvgl_port_lock(0);
    gif_start = lv_gif_create(lv_scr_act());
    lv_gif_set_src(gif_start, &img_bilibili120);
    lv_obj_align(gif_start, LV_ALIGN_CENTER, 0, 0);
    lvgl_port_unlock();
}

// AI人退出屏幕
void ai_gui_out(void)
{
    lvgl_port_lock(0);
    lv_obj_del(gif_start);
    lvgl_port_unlock();
}

// AI播放音乐
void ai_play(void)
{
    int index = file_iterator_get_index(file_iterator);
    ESP_LOGI(TAG, "playing index '%d'", index);
    play_index(index);
    lvgl_port_lock(0);
    lv_label_set_text_static(label_play_pause, LV_SYMBOL_PAUSE); // 显示图标
    lv_obj_add_state(btn_play_pause, LV_STATE_CHECKED);          // 按键设置为选中状态
    lvgl_port_unlock();
}

// AI暂停
void ai_pause(void)
{
    audio_player_pause();
    lvgl_port_lock(0);
    lv_label_set_text_static(label_play_pause, LV_SYMBOL_PLAY); // 显示图标
    lv_obj_clear_state(btn_play_pause, LV_STATE_CHECKED);       // 清除按键的选中状态
    lvgl_port_unlock();
}

// AI继续
void ai_resume(void)
{
    audio_player_resume();
    lvgl_port_lock(0);
    lv_label_set_text_static(label_play_pause, LV_SYMBOL_PAUSE); // 显示图标
    lv_obj_add_state(btn_play_pause, LV_STATE_CHECKED);          // 按键设置为选中状态
    lvgl_port_unlock();
}

// AI上一首
void ai_prev_music(void)
{
    prev_next_music(false);
}

// AI下一首
void ai_next_music(void)
{
    prev_next_music(true);
}

// AI声音大一点
void volume_adjust(int thresh_hold)
{
    g_sys_volume += thresh_hold;
    if (g_sys_volume > 100)
    {
        g_sys_volume = 100;
    }
    else if (g_sys_volume < 0)
    {
        g_sys_volume = 0;
    }
    bsp_codec_volume_set(g_sys_volume, NULL); // 设置声音大小
    lvgl_port_lock(0);
    lv_slider_set_value(volume_slider, g_sys_volume, LV_ANIM_ON); // 设置slider
    lvgl_port_unlock();
}
void ai_volume_up(void)
{
    volume_adjust(5);
}

// AI声音小一点
void ai_volume_down(void)
{
    volume_adjust(-5);
}
