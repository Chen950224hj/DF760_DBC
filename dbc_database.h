#ifndef DBC_DATABASE_H
#define DBC_DATABASE_H

#define j1939can_maxsignal_num 19
#define eqcan_maxsignal_num 73
#define app_ccan_num 30
#define app_pcan_num 12
#define app_rcan_num 9
#define app_rdcan_num 9
#define app_eqcan_num 42
//#define UNSIGNED 0
//#define SIGNED 1
//#define IEEE_FLOAT 2
//#define IEEE_DOUBLE 3

typedef struct {
    double signal_phy[j1939can_maxsignal_num];
    uint8_t* data;
} Message_value;

typedef struct {
    double signal_phy[eqcan_maxsignal_num];
    uint8_t* data;
} Message_eq_value;

typedef struct {
    char sgname[40];
    uint8_t startbit;
    uint8_t length;
    uint8_t mode;
    uint8_t val;
    double factor;
    double offset;
    double min;
    double max;
} Signal_const;

typedef struct {
    char sgname[40];
    uint16_t startbit;
    uint8_t length;
    uint8_t mode;
    uint8_t val;
    double factor;
    double offset;
    double min;
    double max;
} Signal_eq_const;

typedef struct {
    uint32_t id;
    char name[45];
    uint8_t dlc;
    Signal_const signals[j1939can_maxsignal_num];
    uint8_t num_signals;
    char channel[5];
    char trans[2];
    uint8_t cycle;
} Message_const;

typedef struct {
    uint32_t id;
    char name[45];
    uint8_t dlc;
    Signal_eq_const signals[eqcan_maxsignal_num];
    uint8_t num_signals;
    char channel[5];
    char trans[2];
    uint8_t cycle;
} Message_eq_const;

void data_fill(void);
extern Message_value CCAN_t_value[app_ccan_num];
extern const Message_const CCAN_t_const[app_ccan_num];
extern Message_value PCAN_t_value[app_pcan_num];
extern const Message_const PCAN_t_const[app_pcan_num];
extern Message_value RCAN_t_value[app_rcan_num];
extern const Message_const RCAN_t_const[app_rcan_num];
extern Message_value RDCAN_t_value[app_rdcan_num];
extern const Message_const RDCAN_t_const[app_rdcan_num];
extern Message_eq_value EQCAN_t_value[app_eqcan_num];
extern const Message_eq_const EQCAN_t_const[app_eqcan_num];

#endif