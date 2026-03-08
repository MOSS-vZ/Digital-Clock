#include "ti_msp_dl_config.h"
#include "oled.h"
#include "stdbool.h"

char time[20] = "06:00:00";
char timer[20] = "00:00:00";
char time1[20] = "00:00", time2[20] = "00:00", time3[20] = "00:00";
char calendar[20] = "2026/1/17     ";
char ap[3] = "AM";
char pa[3] = "AM";
volatile uint32_t hour = 6, minute = 0, second = 0, carry = 24, year = 2026, month = 1, day = 17;
volatile uint32_t Thour = 0, Tminute = 0, Tsecond = 0;
volatile uint32_t hour1 = 0, hour2 = 0, hour3 = 0, min1 = 0, min2 = 0, min3 = 0;
bool is_transmit = 0, is_time = 0, is_day, is_timer = 0, is_clock = 0, is_carry = 0;

void boot_screen();
char keyboard(void);
void hms_integration(char* time, uint32_t hms[]);
void hms_integration_(char* time, uint32_t hms[]);
void ymd_integration(char* time, uint32_t ymd[]);
void calendar_change(uint32_t* y, uint32_t* m, uint32_t* d);
void hms_into_t(char* c, uint32_t t);
void hms_into_t_(char* c, uint32_t t);
void function_v1();
void function_v2();
void function_v3();
void function_v4();
void date();
void clock(char* t, volatile uint32_t* h, volatile uint32_t* m);
void calendar_to_ymd(char* calendar);
void functional_interface();
void function_v2_interface();
void clock_interface(char* t);
void Timer_interface();
void Clock_interface();
void show_week();
void time_up(char* t);
void transmit_reminder();
uint32_t sethms(uint32_t hms);
bool check_string(char* t);

int main(void)
{

    SYSCFG_DL_init();
    OLED_Init();        //初始化

    boot_screen();
    delay_cycles(32000000);
    OLED_Clear();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//开启定时中断
    DL_Timer_startCounter(TIMER_0_INST);//开启定时器
    DL_TimerG_startCounter(PWM_0_INST);
    DL_TimerG_setCaptureCompareValue(PWM_0_INST, 2500, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    while (1)
    {
        functional_interface();
        char key = keyboard();
        if (key == 'u')
        {
            function_v1();
        }
        else if (key == 'd')
        {
            function_v2();
        }
        else if (key == 'l')
        {
            function_v3();
        }
        else if (key == 'r')
        {
            function_v4();
        }

        // if (is_clock)
        // {
        //     if (check_string(time1))
        //     {
        //         NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);
        //         time_up(time1);
        //         NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
        //     }
        //     else if (check_string(time2))
        //     {
        //         NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);
        //         time_up(time2);
        //         NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
        //     }
        //     else if (check_string(time3))
        //     {
        //         NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);
        //         time_up(time3);
        //         NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
        //     }

        //     is_clock = 0;
        // }
    }
}

void TIMER_0_INST_IRQHandler(void)
{
    uint32_t h = hour, min = minute, s = second, y = year, mon = month, d = day;

    s += 1;
    if (s >= 60)
    {
        s = 0;
        min += 1;
        if (min >= 60)
        {
            min = 0;
            h += 1;
            if (h >= carry && carry == 24)
            {
                h = 0;
                calendar_change(&y, &mon, &d);
            }
            else if (carry == 12)
            {
                if (*ap == 'A' && h == carry)
                {
                    *ap = 'P';
                }
                else if (*ap == 'P' && h > carry)
                {
                    h = 1;
                }
                else if (*ap == 'P' && h == carry)
                {
                    *ap = 'A';
                    h = 0;
                    calendar_change(&y, &mon, &d);
                }
            }
        }
    }

    uint32_t hms[3] = { h,min,s };
    uint32_t ymd[3] = { y,mon,d };

    hms_integration(time, hms);
    ymd_integration(calendar, ymd);

    hour = h;
    minute = min;
    second = s;
    day = d;
    month = mon;
    year = y;

    is_time = 1;
}

void calendar_change(uint32_t* y, uint32_t* m, uint32_t* d)
{
    bool is_m = 0;
    *d += 1;
    switch (*m)
    {
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
        if (*d > 31)
            is_m = 1;
        break;
    case 2:
        if ((*y % 4 == 0 && *y % 100 != 0) || (*y % 400 == 0))
        {
            if (*d > 29)
                is_m = 1;
        }
        else
            if (*d > 28)
                is_m = 1;
        break;
    default:
        if (*d > 30)
            is_m = 1;
        break;
    }
    if (is_m)
    {
        *d = 1;
        *m += 1;
        if (*m > 12)
        {
            *m = 1;
            *y += 1;
        }
    }
}

void hms_integration(char* time, uint32_t hms[])
{
    hms_into_t(time, hms[0]);
    hms_into_t(&time[3], hms[1]);
    hms_into_t(&time[6], hms[2]);
    time[8] = '\0';
}

void hms_integration_(char* time, uint32_t hms[])
{
    hms_into_t_(time, hms[0]);
    hms_into_t_(&time[3], hms[1]);
    time[5] = '\0';
}

void hms_into_t(char* c, uint32_t t)
{
    if (t < 10)
    {
        *c = '0';
        *(c + 1) = t + '0';
    }
    else
    {
        *c = t / 10 + '0';
        *(c + 1) = t % 10 + '0';
    }
}

void hms_into_t_(char* c, uint32_t t)
{
    if (t < 10)
    {
        *c = '0';
        *(c + 1) = t + '0';
    }
    else
    {
        *c = t / 10 + '0';
        *(c + 1) = t % 10 + '0';
    }
}

void ymd_integration(char* time, uint32_t ymd[])
{
    uint32_t y = ymd[0], m = ymd[1], d = ymd[2];
    int i, cnt;
    for (i = 0;i < 4;i++)
    {
        time[3 - i] = y % 10 + '0';
        y /= 10;
    }
    time[4] = '/';
    if (m > 9)
    {
        time[5] = m / 10 + '0';
        time[6] = m % 10 + '0';
        time[7] = '/';
        cnt = 7;
    }
    else
    {
        time[5] = m + '0';
        time[6] = '/';
        cnt = 6;
    }
    if (d > 9)
    {
        time[cnt + 1] = d / 10 + '0';
        time[cnt + 2] = d % 10 + '0';
        for (int i = cnt + 3;i < cnt + 5;i++)
            time[i] = ' ';
        time[cnt + 5] = '\0';
    }
    else
    {
        time[cnt + 1] = d + '0';
        for (int i = cnt + 2;i < cnt + 5;i++)
            time[i] = ' ';
        time[cnt + 5] = '\0';
    }
}

void boot_screen()
{
    OLED_ShowCHinese(16, 2, 15);
    OLED_ShowCHinese(32, 2, 16);
    OLED_ShowCHinese(48, 2, 17);
    OLED_ShowChar(64, 2, ',');
    OLED_ShowCHinese(80, 2, 18);
    OLED_ShowCHinese(96, 2, 19);
    OLED_ShowChar(112, 2, '!');
}

char keyboard(void)
{
    int H_Pin[4] = { KEY_H1_PIN,KEY_H2_PIN,KEY_H3_PIN,KEY_H4_PIN };
    int V_Pin[4] = { KEY_V1_PIN,KEY_V2_PIN,KEY_V3_PIN,KEY_V4_PIN };
    char key_symbol[16] = { '1','2','3','u','4','5','6','d','7','8','9','l','q','0','y','r' };
    int h, v, i;
    for (h = 0;h < 4;h++)
    {
        for (i = 0;i < 4;i++)
        {
            if (i == h)
                DL_GPIO_clearPins(KEY_PORT, H_Pin[i]);
            else
                DL_GPIO_setPins(KEY_PORT, H_Pin[i]);
        }
        delay_cycles(25000);
        for (v = 0;v < 4;v++)
        {
            if (DL_GPIO_readPins(KEY_PORT, V_Pin[v]) == 0)
            {
                delay_cycles(640000);
                if (DL_GPIO_readPins(KEY_PORT, V_Pin[v]) == 0)
                    return key_symbol[h * 4 + v];
            }
        }
    }
    return '\0';
}

void function_v1()
{
    OLED_Clear();
    transmit_reminder();

    bool is_key = 0;
    while (1)
    {
        uint32_t h = hour;
        char local_time[20];
        char local_calendar[20];

        if (is_time)
        {
            int j, i;
            for (i = 0;time[i] != '\0';i++)
                local_time[i] = time[i];
            local_time[i] = '\0';
            for (j = 0;calendar[j] != '\0';j++)
                local_calendar[j] = calendar[j];
            local_calendar[j] = '\0';
            is_time = 0;

            OLED_ShowString(0, 0, local_time);
            if (carry == 24)
                OLED_ShowString(72, 0, "  ");
            else
                OLED_ShowString(72, 0, ap);
            OLED_ShowString(0, 2, local_calendar);
            show_week();
        }

        char key = keyboard();
        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'y')
            {
                if (carry == 24)
                {
                    carry = 12;
                    if (h > 12)
                    {
                        h -= 12;
                        *ap = 'P';
                    }
                    else if (h == 12)
                        *ap = 'P';
                    is_carry = 1;
                }
                else
                {
                    carry = 24;
                    if (*ap == 'P' && h < 12)
                        h += 12;
                }
                hour = h;
            }
            else if (key == 'q')
            {
                break;
            }
        }
        else if (key == '\0')
            is_key = 0;
    }

    OLED_Clear();
}

void function_v2()
{
    NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);
    OLED_Clear();

    while (1)
    {
        function_v2_interface();
        delay_cycles(3200000);

        char key = keyboard();
        uint32_t sethour = hour;
        uint32_t setminute = minute;
        uint32_t setsecond = second;
        if (key == 'u')
        {
            OLED_Clear();
            sethour = sethms(sethour);
            hour = sethour;
        }
        else if (key == 'd')
        {
            OLED_Clear();
            setminute = sethms(setminute);
            minute = setminute;
        }
        else if (key == 'l')
        {
            OLED_Clear();
            setsecond = sethms(setsecond);
            second = setsecond;
        }
        else if (key == 'r')
        {
            OLED_Clear();
            date();
        }
        else if (key == 'q')
        {
            break;
        }
    }

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
}

void change_string(char* a, char* b)
{
    for (int i = 0;b[i] != '\0';i++)
        a[i] = b[i];
}

void function_v3()
{
    NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);
    OLED_Clear();
    Clock_interface();
    delay_cycles(3200000);

    bool is_key = 0;

    while (1)
    {
        char key = keyboard();
        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'u')
            {
                clock(time1, &hour1, &min1);
                OLED_Clear();
                Clock_interface();
            }
            else if (key == 'd')
            {
                clock(time2, &hour2, &min2);
                OLED_Clear();
                Clock_interface();
            }
            else if (key == 'l')
            {
                clock(time3, &hour3, &min3);
                OLED_Clear();
                Clock_interface();
            }
            else if (key == 'q')
                break;
        }
        else if (key == '\0')
            is_key = 0;
    }

    is_clock = 1;

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
}

void function_v4()
{
    NVIC_DisableIRQ(TIMER_0_INST_INT_IRQN);

    OLED_Clear();
    Timer_interface();
    OLED_ShowString(0, 0, timer);

    bool is_key = 0;

    while (1)
    {
        if (is_timer)
        {
            char local_timer[20];
            int i = 0;
            for (i = 0;timer[i] != '\0';i++)
                local_timer[i] = timer[i];
            local_timer[i] = '\0';
            is_timer = 0;
            OLED_ShowString(0, 0, local_timer);
        }

        char key = keyboard();
        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'u')
            {
                DL_Timer_startCounter(TIMER_1_INST);
                NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);
            }
            else if (key == 'd')
            {
                NVIC_DisableIRQ(TIMER_1_INST_INT_IRQN);
                DL_Timer_stopCounter(TIMER_1_INST);
            }
            else if (key == 'l')
            {
                change_string(timer, "00:00:00");
                Thour = 0;
                Tminute = 0;
                Tsecond = 0;
                is_timer = 1;
            }
            else if (key == 'q')
                break;
        }
        else if (key == '\0')
            is_key = 0;
    }

    OLED_Clear();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
}

void TIMER_1_INST_IRQHandler(void)
{
    uint32_t h = Thour, min = Tminute, s = Tsecond;
    s += 1;
    if (s >= 60)
    {
        s = 0;
        min += 1;
        if (min >= 60)
        {
            min = 0;
            h += 1;
            if (h > 99)
                h = 0;
        }
    }

    uint32_t hms[3] = { h,min,s };

    hms_integration(timer, hms);

    Thour = h;
    Tminute = min;
    Tsecond = s;

    is_timer = 1;
}

void clock(char* t, volatile uint32_t* h, volatile uint32_t* m)
{
    OLED_Clear();

    if (carry == 12)
    {
        OLED_ShowString(54, 0, pa);
        is_carry = 0;
    }
    else
        OLED_ShowString(54, 0, "  ");

    while (1)
    {
        clock_interface(t);
        delay_cycles(3200000);

        char key = keyboard();
        if (key == 'u')
        {
            OLED_Clear();
            *h = sethms(*h);
            uint32_t hms[2] = { *h,*m };
            hms_integration_(t, hms);
            OLED_Clear();
        }
        else if (key == 'd')
        {
            OLED_Clear();
            *m = sethms(*m);
            uint32_t hms[2] = { *h,*m };
            hms_integration_(t, hms);
            OLED_Clear();
        }
        else if (key == 'q')
        {
            break;
        }
    }
}

uint32_t sethms(uint32_t hms)
{
    OLED_ShowCHinese(0, 4, 26);
    OLED_ShowChar(18, 4, 'q');
    OLED_ShowCHinese(34, 4, 34);
    OLED_ShowCHinese(50, 4, 35);
    OLED_ShowCHinese(0, 6, 26);
    OLED_ShowChar(18, 6, 'y');
    OLED_ShowCHinese(34, 6, 32);
    OLED_ShowCHinese(50, 6, 33);

    bool is_key = 0;
    char chms[3];

    while (1)
    {
        if (hms > 9)
        {
            chms[0] = hms / 10 + '0';
            chms[1] = hms % 10 + '0';
            chms[2] = '\0';
        }
        else
        {
            chms[0] = ' ';
            chms[1] = hms + '0';
            chms[2] = '\0';
        }

        OLED_ShowString(0, 0, chms);

        char key = keyboard();
        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'q')
            {
                hms = 0;
            }
            else if (key >= '0' && key <= '9')
            {
                hms = hms * 10 + (key - '0');
            }
            else if (key == 'y')
                break;
        }
        else if (key == '\0')
            is_key = 0;
    }
    return hms;
}

void date()
{
    bool is_key = 0;
    int i = 0;

    char local_calendar[20];
    int j;
    for (j = 0;calendar[j] != '\0';j++)
        local_calendar[j] = calendar[j];
    local_calendar[j] = '\0';

    while (1)
    {
        OLED_ShowString(0, 0, local_calendar);
        OLED_ShowCHinese(0, 4, 26);
        OLED_ShowChar(18, 4, 'q');
        OLED_ShowCHinese(34, 4, 34);
        OLED_ShowCHinese(50, 4, 35);
        OLED_ShowCHinese(0, 6, 26);
        OLED_ShowChar(18, 6, 'y');
        OLED_ShowCHinese(34, 6, 32);
        OLED_ShowCHinese(50, 6, 33);

        char key = keyboard();
        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'q')
            {
                OLED_Clear();
                local_calendar[0] = '\0';
                i = 0;
            }
            else if (key >= '0' && key <= '9')
            {
                local_calendar[i++] = key;
                local_calendar[i] = '\0';
            }
            else if (key == 'u')
            {
                local_calendar[i++] = '/';
                local_calendar[i] = '\0';
            }
            else if (key == 'y')
                break;
        }
        else if (key == '\0')
            is_key = 0;
    }

    calendar_to_ymd(local_calendar);

    OLED_Clear();
}

void calendar_to_ymd(char* calendar)
{
    uint32_t y = 0, m = 0, d = 0;
    int m_i = 0, d_i = 0;
    for (int i = 0;calendar[i] != '\0';i++)
    {
        if (calendar[i] == '/' && m_i == 0)
            m_i = i;
        else if (calendar[i] == '/' && m_i != 0)
            d_i = i;
    }
    for (int i = 0;i < m_i;i++)
    {
        y = y * 10 + (calendar[i] - '0');
    }
    for (int i = m_i + 1;i < d_i;i++)
    {
        m = m * 10 + (calendar[i] - '0');
    }
    for (int i = d_i + 1;calendar[i] != '\0';i++)
    {
        d = d * 10 + (calendar[i] - '0');
    }
    year = y;
    month = m;
    day = d;
}

bool check_string(char* t)
{
    for (int i = 0;t[i] != '\0';i++)
    {
        if (time[i] != t[i])
            return 0;
    }
    return 1;
}
void functional_interface()
{
    OLED_ShowCHinese(0, 0, 24);
    OLED_ShowCHinese(16, 0, 25);
    OLED_ShowCHinese(32, 0, 0);
    OLED_ShowCHinese(48, 0, 1);
    OLED_ShowCHinese(96, 0, 26);
    OLED_ShowChar(114, 0, 'u');

    OLED_ShowCHinese(0, 2, 22);
    OLED_ShowCHinese(16, 2, 23);
    OLED_ShowCHinese(32, 2, 0);
    OLED_ShowCHinese(48, 2, 1);
    OLED_ShowCHinese(96, 2, 26);
    OLED_ShowChar(114, 2, 'd');

    OLED_ShowCHinese(0, 4, 22);
    OLED_ShowCHinese(16, 4, 23);
    OLED_ShowCHinese(32, 4, 27);
    OLED_ShowCHinese(48, 4, 28);
    OLED_ShowCHinese(96, 4, 26);
    OLED_ShowChar(114, 4, 'l');

    OLED_ShowCHinese(0, 6, 22);
    OLED_ShowCHinese(16, 6, 23);
    OLED_ShowCHinese(32, 6, 29);
    OLED_ShowCHinese(48, 6, 0);
    OLED_ShowCHinese(64, 6, 30);
    OLED_ShowCHinese(96, 6, 26);
    OLED_ShowChar(114, 6, 'r');
}

void function_v2_interface()
{
    OLED_ShowCHinese(0, 0, 22);
    OLED_ShowCHinese(16, 0, 23);
    OLED_ShowCHinese(32, 0, 31);
    OLED_ShowCHinese(48, 0, 0);
    OLED_ShowCHinese(96, 0, 26);
    OLED_ShowChar(114, 0, 'u');

    OLED_ShowCHinese(0, 2, 22);
    OLED_ShowCHinese(16, 2, 23);
    OLED_ShowCHinese(32, 2, 2);
    OLED_ShowCHinese(48, 2, 17);
    OLED_ShowCHinese(96, 2, 26);
    OLED_ShowChar(114, 2, 'd');

    OLED_ShowCHinese(0, 4, 22);
    OLED_ShowCHinese(16, 4, 23);
    OLED_ShowCHinese(32, 4, 3);
    OLED_ShowCHinese(48, 4, 17);
    OLED_ShowCHinese(96, 4, 26);
    OLED_ShowChar(114, 4, 'l');

    OLED_ShowCHinese(0, 6, 22);
    OLED_ShowCHinese(16, 6, 23);
    OLED_ShowCHinese(32, 6, 20);
    OLED_ShowCHinese(48, 6, 11);
    OLED_ShowCHinese(64, 6, 21);
    OLED_ShowCHinese(96, 6, 26);
    OLED_ShowChar(114, 6, 'r');
}

void clock_interface(char* t)
{
    OLED_ShowString(0, 0, t);

    OLED_ShowCHinese(0, 2, 22);
    OLED_ShowCHinese(16, 2, 23);
    OLED_ShowCHinese(32, 2, 31);
    OLED_ShowCHinese(48, 2, 0);
    OLED_ShowCHinese(96, 2, 26);
    OLED_ShowChar(114, 2, 'u');

    OLED_ShowCHinese(0, 4, 22);
    OLED_ShowCHinese(16, 4, 23);
    OLED_ShowCHinese(32, 4, 2);
    OLED_ShowCHinese(48, 4, 17);
    OLED_ShowCHinese(96, 4, 26);
    OLED_ShowChar(114, 4, 'd');
}

void Timer_interface()
{
    OLED_ShowCHinese(0, 4, 26);
    OLED_ShowChar(16, 4, 'u');
    OLED_ShowCHinese(25, 4, 38);
    OLED_ShowCHinese(41, 4, 18);

    OLED_ShowCHinese(70, 4, 26);
    OLED_ShowChar(86, 4, 'd');
    OLED_ShowCHinese(97, 4, 39);
    OLED_ShowCHinese(113, 4, 40);

    OLED_ShowCHinese(0, 6, 26);
    OLED_ShowChar(16, 6, 'l');
    OLED_ShowCHinese(25, 6, 34);
    OLED_ShowCHinese(41, 6, 35);

    OLED_ShowCHinese(70, 6, 26);
    OLED_ShowChar(86, 6, 'q');
    OLED_ShowCHinese(97, 6, 41);
    OLED_ShowCHinese(113, 6, 42);
}

void Clock_interface()
{
    OLED_ShowCHinese(0, 0, 27);
    OLED_ShowCHinese(16, 0, 28);
    OLED_ShowChar(32, 0, '1');
    OLED_ShowCHinese(96, 0, 26);
    OLED_ShowChar(114, 0, 'u');

    OLED_ShowCHinese(0, 2, 27);
    OLED_ShowCHinese(16, 2, 28);
    OLED_ShowChar(32, 2, '2');
    OLED_ShowCHinese(96, 2, 26);
    OLED_ShowChar(114, 2, 'd');

    OLED_ShowCHinese(0, 4, 27);
    OLED_ShowCHinese(16, 4, 28);
    OLED_ShowChar(32, 4, '3');
    OLED_ShowCHinese(96, 4, 26);
    OLED_ShowChar(114, 4, 'l');

    OLED_ShowCHinese(0, 6, 26);
    OLED_ShowChar(16, 6, 'q');
    OLED_ShowCHinese(27, 6, 41);
    OLED_ShowCHinese(43, 6, 42);
}

int zellers_formula(int year, int month, int day) {
    int m, y, c, d;

    // 对1月和2月进行处理
    if (month < 3) {
        m = month + 12;
        y = year - 1;
    }
    else {
        m = month;
        y = year;
    }

    c = y / 100;  // 世纪数
    d = y % 100;  // 年份后两位

    // 蔡勒公式
    int h = (day + (13 * (m + 1)) / 5 + d + d / 4 + c / 4 - 2 * c) % 7;

    // 调整结果为非负数
    if (h < 0) {
        h += 7;
    }

    return h;
}

void show_week()
{
    OLED_ShowCHinese(0, 4, 13);
    OLED_ShowCHinese(16, 4, 14);
    int w = zellers_formula(year, month, day);
    OLED_ShowCHinese(32, 4, w + 4);
}

void transmit_reminder()
{
    OLED_ShowCHinese(0, 6, 26);
    OLED_ShowChar(16, 6, 'y');
    OLED_ShowCHinese(25, 6, 36);
    OLED_ShowCHinese(41, 6, 37);
    OLED_ShowString(57, 6, "12/24");
}

void time_up(char* t)
{
    OLED_Clear();
    char key = keyboard();
    bool is_key = 0;

    while (1)
    {
        OLED_ShowString(2, 36, t);

        OLED_ShowCHinese(4, 32, 27);
        OLED_ShowCHinese(4, 48, 28);
        OLED_ShowCHinese(4, 64, 0);
        OLED_ShowCHinese(4, 80, 1);
        OLED_ShowCHinese(4, 96, 43);

        OLED_ShowCHinese(0, 6, 26);
        OLED_ShowChar(16, 6, 'q');
        OLED_ShowCHinese(27, 6, 41);
        OLED_ShowCHinese(43, 6, 42);

        if (key && !is_key)
        {
            is_key = 1;
            if (key == 'q')
                break;
        }
        else if (key == '\0')
            is_key = 0;
    }
}