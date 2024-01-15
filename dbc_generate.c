#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 150
#define NUM_DBCFILE 5
#define APP_EQ_NUM 40
#define APP_NUM 92                  //APP message num

//定义Signal结构体
typedef struct {
    char sgname[40];
    int startbit;
    int length;
    int mode;
    int val;
    char factor[30];
    char offset[30];
    char min[30];
    char max[30];
} Signal;

//定义Message结构体
typedef struct {
    char id[20];
    char name[45];
    int dlc;
    Signal signals[100];
    int num_signals;
    int cycle;
} Message;

//定义应用层normal信号列表
typedef struct {
    char Signalname[20][45];
} APPSignallist;

//定义应用层eq信号列表
typedef struct {
    char Signalname[80][45];
} APP_EQ_Signallist;

//定义应用层normal message结构体
typedef struct {
    char channel[6];
    char Messagename[45];
    char transmit[2];
    int signalnum;
    APPSignallist appsignallist;
} APPMessagelist;

//定义应用层EQ_message结构体
typedef struct {
    char channel[6];
    char Messagename[45];
    char transmit[2];
    int signalnum;
    APP_EQ_Signallist appsignallist;
} APP_EQ_Messagelist;

typedef struct {
    char  id[20];
    char name[45];
    int dlc;
    Signal signals[80];
    int num_signals;
    int cycle;
    char CAN[6];
    char trans[2];
} REAL_Message;

FILE *fp = NULL;

static void dbc_databaseh_title_add(FILE* file, int appcnum, int apppnum, int apprnum, int apprdnum, int appeqnum, int j1939canmaxsignalnum, int eqcanmaxsignalnum){
    fprintf(file, "#ifndef DBC_DATABASE_H\n");
    fprintf(file, "#define DBC_DATABASE_H\n");
    fprintf(file, "\n");

    fprintf(file, "#define j1939can_maxsignal_num %d\n", j1939canmaxsignalnum);
    fprintf(file, "#define eqcan_maxsignal_num %d\n", eqcanmaxsignalnum);
    fprintf(file, "#define app_ccan_num %d\n", appcnum);
    fprintf(file, "#define app_pcan_num %d\n", apppnum);
    fprintf(file, "#define app_rcan_num %d\n", apprnum);
    fprintf(file, "#define app_rdcan_num %d\n", apprdnum);
    fprintf(file, "#define app_eqcan_num %d\n", appeqnum);
    fprintf(file, "//#define UNSIGNED 0\n");
    fprintf(file, "//#define SIGNED 1\n");
    fprintf(file, "//#define IEEE_FLOAT 2\n");
    fprintf(file, "//#define IEEE_DOUBLE 3\n");
    fprintf(file, "\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    double signal_phy[j1939can_maxsignal_num];\n");
    fprintf(file, "    uint8_t* data;\n");
    fprintf(file, "} Message_value;\n");
    fprintf(file, "\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    double signal_phy[eqcan_maxsignal_num];\n");
    fprintf(file, "    uint8_t* data;\n");
    fprintf(file, "} Message_eq_value;\n");
    fprintf(file, "\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    char sgname[40];\n");
    fprintf(file, "    uint8_t startbit;\n");
    fprintf(file, "    uint8_t length;\n");
    fprintf(file, "    uint8_t mode;\n");
    fprintf(file, "    uint8_t val;\n");
    fprintf(file, "    double factor;\n");
    fprintf(file, "    double offset;\n");
    fprintf(file, "    double min;\n");
    fprintf(file, "    double max;\n");
    fprintf(file, "} Signal_const;\n");
    fprintf(file, "\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    char sgname[40];\n");
    fprintf(file, "    uint16_t startbit;\n");
    fprintf(file, "    uint8_t length;\n");
    fprintf(file, "    uint8_t mode;\n");
    fprintf(file, "    uint8_t val;\n");
    fprintf(file, "    double factor;\n");
    fprintf(file, "    double offset;\n");
    fprintf(file, "    double min;\n");
    fprintf(file, "    double max;\n");
    fprintf(file, "} Signal_eq_const;\n");
    fprintf(file, "\n");
    
    fprintf(file, "typedef struct {\n");
    fprintf(file, "    uint32_t id;\n");
    fprintf(file, "    char name[45];\n");
    fprintf(file, "    uint8_t dlc;\n");
    fprintf(file, "    Signal_const signals[j1939can_maxsignal_num];\n");
    fprintf(file, "    uint8_t num_signals;\n");
    fprintf(file, "    char channel[5];\n");
    fprintf(file, "    char trans[2];\n");
    fprintf(file, "    uint8_t cycle;\n");
    fprintf(file, "} Message_const;\n");
    fprintf(file, "\n");

    fprintf(file, "typedef struct {\n");
    fprintf(file, "    uint32_t id;\n");
    fprintf(file, "    char name[45];\n");
    fprintf(file, "    uint8_t dlc;\n");
    fprintf(file, "    Signal_eq_const signals[eqcan_maxsignal_num];\n");
    fprintf(file, "    uint8_t num_signals;\n");
    fprintf(file, "    char channel[5];\n");
    fprintf(file, "    char trans[2];\n");
    fprintf(file, "    uint8_t cycle;\n");
    fprintf(file, "} Message_eq_const;\n");
    fprintf(file, "\n");

    fprintf(file, "void data_fill(void);\n");

    fprintf(file, "extern Message_value CCAN_t_value[app_ccan_num];\n");
    fprintf(file, "extern const Message_const CCAN_t_const[app_ccan_num];\n");
    fprintf(file, "extern Message_value PCAN_t_value[app_pcan_num];\n");
    fprintf(file, "extern const Message_const PCAN_t_const[app_pcan_num];\n");
    fprintf(file, "extern Message_value RCAN_t_value[app_rcan_num];\n");
    fprintf(file, "extern const Message_const RCAN_t_const[app_rcan_num];\n");
    fprintf(file, "extern Message_value RDCAN_t_value[app_rdcan_num];\n");
    fprintf(file, "extern const Message_const RDCAN_t_const[app_rdcan_num];\n");
    fprintf(file, "extern Message_eq_value EQCAN_t_value[app_eqcan_num];\n");
    fprintf(file, "extern const Message_eq_const EQCAN_t_const[app_eqcan_num];\n");
    fprintf(file, "\n");

    fprintf(file, "#endif");
    fclose(file);
}
static void dbc_databasec_title_add(FILE* file){
    fprintf(file, "#include <stdio.h>\n");
    fprintf(file, "#include <stdlib.h>\n");
    fprintf(file, "#include <string.h>\n");
    fprintf(file, "#include <stdint.h>\n");
    fprintf(file, "#include \"dbc_database.h\"\n");
    fprintf(file, "\n");
    fprintf(file, "#define DEFAULT_VALUE 0xFF\n");
}
static void dbc_databasec_CAN_t_value_add(FILE* file){
    fprintf(file, "Message_value CCAN_t_value[app_ccan_num]={[0 ...(app_ccan_num-1)]={.data=NULL, .signal_phy={0}}};\n");
    fprintf(file, "Message_value PCAN_t_value[app_pcan_num]={[0 ...(app_pcan_num-1)]={.data=NULL, .signal_phy={0}}};\n");
    fprintf(file, "Message_value RCAN_t_value[app_rcan_num]={[0 ...(app_rcan_num-1)]={.data=NULL, .signal_phy={0}}};\n");
    fprintf(file, "Message_value RDCAN_t_value[app_rdcan_num]={[0 ...(app_rdcan_num-1)]={.data=NULL, .signal_phy={0}}};\n");
    fprintf(file, "Message_eq_value EQCAN_t_value[app_eqcan_num]={[0 ...(app_eqcan_num-1)]={.data=NULL, .signal_phy={0}}};\n");
}
static void dbc_databasec_CAN_t_const_add(FILE* file, int appcnum, int apppnum, int apprnum, int apprdnum, int appeqnum, REAL_Message *real_message){
    for(int i = 0; i < APP_NUM; i++)
    {
        //输出各路CAN表头
        if(i == 0)
        {
            fprintf(fp, "const Message_const CCAN_t_const[app_ccan_num]={\n");
        }else if(i == appcnum){
            fprintf(fp, "const Message_const PCAN_t_const[app_pcan_num]={\n");
        }else if(i == (appcnum + apppnum)){
            fprintf(fp, "const Message_const RCAN_t_const[app_rcan_num]={\n");
        }else if(i == (appcnum + apppnum + apprnum)){
            fprintf(fp, "const Message_const RDCAN_t_const[app_rdcan_num]={\n");
        }else if(i == (appcnum + apppnum + apprnum + apprdnum)){
            fprintf(fp, "const Message_eq_const EQCAN_t_const[app_eqcan_num]={\n");
        }
        fprintf(fp,"        {\n");
        fprintf(fp,"            .id=%s, .name=\"%s\", .dlc=%d, .num_signals=%d, .trans=\"%.*s\", .cycle=%d, .signals=\n", real_message[i].id, real_message[i].name, real_message[i].dlc, real_message[i].num_signals, 2, real_message[i].trans, real_message[i].cycle);   
        fprintf(fp,"            {\n");
        for (int j = 0; j < real_message[i].num_signals; j++){
            Signal *s = &real_message[i].signals[j];
            fprintf(fp,"                {.sgname=\"%s\", .startbit=%d, .length=%d, .mode=%d, .factor=%s, .offset=%s, .min=%s, .max=%s, ",
                s->sgname, s->startbit, s->length, s->mode, s->factor, s->offset, s->min, s->max);
            if(s->val == 0){
                fprintf(fp,".val=0},\n");
            }else if(s->val == 1){
                fprintf(fp,".val=1},\n");
            }else if(s->val == 2){
                fprintf(fp,".val=2},\n");
            }else if(s->val == 3){                          //EQ DBC错误，修正
                fprintf(fp,".val=2},\n");
            }
        }
        fprintf(fp,"            },\n");
        if (i == (appcnum - 1) || i == (appcnum + apppnum - 1) || i == (appcnum + apppnum + apprnum - 1) || i == (appcnum + apppnum + apprnum + apprdnum - 1) || i == (APP_NUM - 1)){
            fprintf(fp,"        }\n");
            fprintf(fp, "};\n");
        } else {
            fprintf(fp,"        },\n");
        }
    }
}
static void dbc_databasec_end_add(FILE* file){
    fprintf(file, "void data_fill(void)\n");
    fprintf(file, "{\n");
    fprintf(file, "    for(uint8_t i = 0; i < 5; i++)\n");
    fprintf(file, "    {\n");
    fprintf(file, "        if(i == 0)\n");
    fprintf(file, "        {\n");
    fprintf(file, "            for(uint8_t j = 0; j < app_ccan_num; j++)\n");
    fprintf(file, "            {\n");
    fprintf(file, "                if(strncmp(CCAN_t_const[j].trans, \"Tx\", 2) == 0)\n");
    fprintf(file, "                {\n");
    fprintf(file, "                    CCAN_t_value[j].data = (uint8_t*)malloc(CCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                    volatile uint8_t *p = CCAN_t_value[j].data;\n");
    fprintf(file, "                    memset((void *)p, DEFAULT_VALUE, CCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                }\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "        if(i == 1)\n");
    fprintf(file, "        {\n");
    fprintf(file, "            for(uint8_t j = 0; j < app_pcan_num; j++)\n");
    fprintf(file, "            {\n");
    fprintf(file, "                if(strncmp(PCAN_t_const[j].trans, \"Tx\", 2) == 0)\n");
    fprintf(file, "                {\n");
    fprintf(file, "                    PCAN_t_value[j].data = (uint8_t*)malloc(PCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                    volatile uint8_t *p = PCAN_t_value[j].data;\n");
    fprintf(file, "                    memset((void *)p, DEFAULT_VALUE, PCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                }\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "        if(i == 2)\n");
    fprintf(file, "        {\n");
    fprintf(file, "            for(uint8_t j = 0; j < app_rcan_num; j++)\n");
    fprintf(file, "            {\n");
    fprintf(file, "                if(strncmp(RCAN_t_const[j].trans, \"Tx\", 2) == 0)\n");
    fprintf(file, "                {\n");
    fprintf(file, "                    RCAN_t_value[j].data = (uint8_t*)malloc(RCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                    volatile uint8_t *p = RCAN_t_value[j].data;\n");
    fprintf(file, "                    memset((void *)p, DEFAULT_VALUE, RCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                }\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "        if(i == 3)\n");
    fprintf(file, "        {\n");
    fprintf(file, "            for(uint8_t j = 0; j < app_rdcan_num; j++)\n");
    fprintf(file, "            {\n");
    fprintf(file, "                if(strncmp(RDCAN_t_const[j].trans, \"Tx\", 2) == 0)\n");
    fprintf(file, "                {\n");
    fprintf(file, "                    RDCAN_t_value[j].data = (uint8_t*)malloc(RDCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                    volatile uint8_t *p = RDCAN_t_value[j].data;\n");
    fprintf(file, "                    memset((void *)p, DEFAULT_VALUE, RDCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                }\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "        if(i == 4)\n");
    fprintf(file, "        {\n");
    fprintf(file, "            for(uint8_t j = 0; j < app_eqcan_num; j++)\n");
    fprintf(file, "            {\n");
    fprintf(file, "                if(strncmp(EQCAN_t_const[j].trans, \"Tx\", 2) == 0)\n");
    fprintf(file, "                {\n");
    fprintf(file, "                    EQCAN_t_value[j].data = (uint8_t*)malloc(EQCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                    volatile uint8_t *p = EQCAN_t_value[j].data;\n");
    fprintf(file, "                    memset((void *)p, DEFAULT_VALUE, EQCAN_t_const[j].dlc * sizeof(uint8_t));\n");
    fprintf(file, "                }\n");
    fprintf(file, "            }\n");
    fprintf(file, "        }\n");
    fprintf(file, "    }\n");
    fprintf(file, "};\n");
}

int main(void) {

    Message *messages = malloc(sizeof(Message));
    char dbc_filepath[NUM_DBCFILE][MAX_LINE_LENGTH];
    //DBC filepath
    strcpy(dbc_filepath[0], "C:\\Users\\PC-1\\Desktop\\Capl_CCAN_test_0306\\database\\20220402-DF-CCAN-V0.8.1.dbc");
    strcpy(dbc_filepath[1], "C:\\Users\\PC-1\\Desktop\\Capl_CCAN_test_0306\\database\\DF_PCAN_TgtSpd_V1.1.2_20220825.dbc");
    strcpy(dbc_filepath[2], "C:\\Users\\PC-1\\Desktop\\Capl_CCAN_test_0306\\database\\DF RCAN-V0.9.3_20220825.dbc");
    strcpy(dbc_filepath[3], "C:\\Users\\PC-1\\Desktop\\Capl_CCAN_test_0306\\database\\RDF2_ARS430CS11.dbc");
    strcpy(dbc_filepath[4], "C:\\Users\\PC-1\\Desktop\\Capl_CCAN_test_0306\\database\\Hirain_Trunk_EQ_4.20.5_V1.2_20210311.dbc");

    APPMessagelist messageList[APP_NUM-APP_EQ_NUM];
    APP_EQ_Messagelist EQ_messageList[APP_EQ_NUM];
    REAL_Message real_message[APP_NUM];
    char app_filepath[MAX_LINE_LENGTH];
    //算法signallist路径
    strcpy(app_filepath, "E:\\signallist.txt");

    int num_messages = 0;
    int message_size = 1;

    char line[MAX_LINE_LENGTH];
    char factor[30], offset[30], min[30], max[30], id[20];
    int m = 0, CCAN_MES_NUM, PCAN_MES_NUM, RCAN_MES_NUM, RDCAN_MES_NUM, EQCAN_MES_NUM, dlc, startbit, mode, length, MESSAGE_INDEX_ARRAY[5] = {};
    char val, token[45], sgname[35];
    int message_index = -1;
    int signal_index = -1;
    char channel[6], Messagename[45], Signalname[45], transmit[2], compare[30];
    int applist_size = 1, appmessagelist_index = -1, appeqmessagelist_index = -1, appsignallist_index;
    int app_ccan_num = 0, app_pcan_num = 0, app_rcan_num = 0, app_rdcan_num = 0, app_eqcan_num = 0;
    char cyc_id[20], signal_valuetype_name[30]; 
    int cyc_time, a, b, c, d, e, j1939can_maxsignal_num = 0, eqcan_maxsignal_num = 0, signal_valuetype = 0;

    //APP全信号提取
    FILE* file = fopen(app_filepath, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", app_filepath);
        return 0;
    }
    
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL){
        // printf("%s",line);
        // if (strncmp(dbc_filepath[0], "C:", 2) != 0)
        // {
        //     int aa = 1;
        // }
        if (strncmp(line, "CCAN", 4) == 0 || strncmp(line, "PCAN", 4) == 0 || strncmp(line, "RCAN", 4) == 0 || strncmp(line, "RDCAN", 5) == 0)
        {
            appsignallist_index = -1;
            appmessagelist_index++;
            sscanf(line, "%s %s %s", channel, Messagename, transmit);
            strcpy(messageList[appmessagelist_index].channel, channel);
            strcpy(messageList[appmessagelist_index].Messagename, Messagename);
            strcpy(messageList[appmessagelist_index].transmit, transmit);
            messageList[appmessagelist_index].signalnum = 0;
            if (strncmp(line, "CCAN", 4) == 0)
            {
                app_ccan_num++;
                messageList[appmessagelist_index].channel[sizeof("CCAN")-1] = '\0';
            }else if(strncmp(line, "PCAN", 4) == 0){
                app_pcan_num++;
                messageList[appmessagelist_index].channel[sizeof("CCAN")-1] = '\0';
            }else if(strncmp(line, "RCAN", 4) == 0){
                app_rcan_num++;
                messageList[appmessagelist_index].channel[sizeof("CCAN")-1] = '\0';
            }else if(strncmp(line, "RDCAN", 5) == 0){
                app_rdcan_num++;
                messageList[appmessagelist_index].channel[sizeof("RDCAN")-1] = '\0';
            }
        }else if(strncmp(line, "EQCAN", 5) == 0){
                app_eqcan_num++;
                appsignallist_index = -1;
                appeqmessagelist_index++;
                sscanf(line, "%s %s %s", channel, Messagename, transmit);
                strcpy(EQ_messageList[appeqmessagelist_index].channel, channel);
                EQ_messageList[appeqmessagelist_index].channel[sizeof("RDCAN")-1] = '\0';
                strcpy(EQ_messageList[appeqmessagelist_index].Messagename, Messagename);
                strcpy(EQ_messageList[appeqmessagelist_index].transmit, transmit);
                EQ_messageList[appeqmessagelist_index].signalnum = 0;
        }else if(strncmp(line, "		", 2) == 0){
            appsignallist_index ++;
            messageList[appmessagelist_index].signalnum++;
            sscanf(line, "%s", Signalname);
            strcpy(messageList[appmessagelist_index].appsignallist.Signalname[appsignallist_index], Signalname);
        }else if(strncmp(line, "EQ	", 3) == 0){
            appsignallist_index ++;
            EQ_messageList[appeqmessagelist_index].signalnum++;
            sscanf(line, "%*s %s", Signalname);
            strcpy(EQ_messageList[appeqmessagelist_index].appsignallist.Signalname[appsignallist_index], Signalname);
        }
    }
    fclose(file);

    //DBC全信号提取
    for (int i = 0; i < NUM_DBCFILE; i++){
        
        FILE* file = fopen(dbc_filepath[i], "r");
        if (file == NULL) {
           printf("Failed to open file: %s\n", dbc_filepath[i]);
           return 0;
        }

        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            //printf("%s",line);
            if (strncmp(line, "BO_ ", 4) == 0) {
                message_index++;
                signal_index = -1;
                sscanf(line, "BO_ %s %[^:]: %d", &id, token, &dlc);
                strcpy(messages[message_index].id, id);
                strcpy(messages[message_index].name, token);
                messages[message_index].dlc = dlc;
                messages[message_index].num_signals = 0;
            }else if (strncmp(line, " SG_", 4) == 0) {
                signal_index++;
                sscanf(line, " SG_ %s : %d|%d@%d%c (%[^,],%[^)]) [%[^|]|%[^]]",
                sgname, &startbit, &length, &mode, &val, factor, offset, min, max);
                if(val == '+'){
                   messages[message_index].signals[signal_index].val = 0;
                }
                else{
                   messages[message_index].signals[signal_index].val = 1;
                }
                strcpy(messages[message_index].signals[signal_index].sgname, sgname);
                messages[message_index].signals[signal_index].startbit = startbit;
                messages[message_index].signals[signal_index].length = length;
                messages[message_index].signals[signal_index].mode = mode;
                strcpy(messages[message_index].signals[signal_index].factor, factor);
                strcpy(messages[message_index].signals[signal_index].offset, offset);
                strcpy(messages[message_index].signals[signal_index].min, min);
                strcpy(messages[message_index].signals[signal_index].max, max);
                messages[message_index].num_signals++;
                long int position = ftell(file);                
                fgets(line, MAX_LINE_LENGTH, file);
                if (line[0] == '\n') {
                    message_size++;
                    messages = realloc(messages, message_size * sizeof(Message));
                }
                fseek(file, position, SEEK_SET);
            }else if(strncmp(line, "BA_ \"GenMsgCycleTime\" BO_ ", 26) == 0){               //周期提取
                sscanf(line, "BA_ \"GenMsgCycleTime\" BO_ %s %d", cyc_id, &cyc_time);
                //CPRcan提取，将cycle time放到message结构体里面
                if(i == 0)
                {
                    a = message_size - 1;
                }else if(i == 1)
                {
                    b = message_size - 1;
                }else if(i == 2)
                {
                    c = message_size - 1;
                }else if(i == 3)
                {
                    d = message_size - 1;
                }else if(i == 4)
                {
                    e = message_size - 1;
                }
                if(i == 0)
                {
                    for(int g = 0; g < a; g++)
                    {
                        if (strcmp(cyc_id, messages[g].id) == 0)
                        {
                            messages[g].cycle = cyc_time;
                            break;
                        }
                    }
                }else if(i == 1){
                    for(int g = a; g < b; g++)
                    {
                        if (strcmp(cyc_id, messages[g].id) == 0)
                        {
                            messages[g].cycle = cyc_time;
                            break;
                        }
                    }
                }else if(i == 2){
                    for(int g = b; g < c; g++)
                    {
                        if (strcmp(cyc_id, messages[g].id) == 0)
                        {
                            messages[g].cycle = cyc_time;
                            break;
                        }
                    }
                }else if(i == 3){
                    for(int g = c; g < d; g++)
                    {
                        if (strcmp(cyc_id, messages[g].id) == 0)
                        {
                            messages[g].cycle = cyc_time;
                            break;
                        }
                    }
                }else if(i == 4){
                    for(int g = d; g < e; g++)
                    {
                        if (strcmp(cyc_id, messages[g].id) == 0)
                        {
                            messages[g].cycle = cyc_time;
                            break;
                        }
                    }
                }
            }
        }

        fclose(file);
        m++;
        MESSAGE_INDEX_ARRAY[m] = message_size;
    }

    //ALL DBC各路CANmessage数量
    CCAN_MES_NUM = MESSAGE_INDEX_ARRAY[1] -1;                               //CCAN总message数
    PCAN_MES_NUM = MESSAGE_INDEX_ARRAY[2] - MESSAGE_INDEX_ARRAY[1];         //PCAN总message数
    RCAN_MES_NUM = MESSAGE_INDEX_ARRAY[3] - MESSAGE_INDEX_ARRAY[2];         //RCAN总message数
    RDCAN_MES_NUM = MESSAGE_INDEX_ARRAY[4] - MESSAGE_INDEX_ARRAY[3];        //RDCAN总message数
    EQCAN_MES_NUM = message_size - MESSAGE_INDEX_ARRAY[4];                  //EQCAN总message数
    message_size -= 1;                                                      //总message数

    //遍历应用层message list
    for(int i = 0; i < APP_NUM; i++)
    {
        if(i < (APP_NUM - APP_EQ_NUM))
        {
            if(strcmp(messageList[i].channel, "CCAN") == 0)                     //CCAN遍历
            {
                for(int j = 0; j < CCAN_MES_NUM - 1; j++)                       //遍历ALL DBC中CCAN message
                {
                    if(strcmp(messageList[i].Messagename, messages[j].name) == 0)   //判断如果app与dbc中message name一样，将相关数据copy到real_message结构体
                    {
                        strcpy(real_message[i].id, messages[j].id);
                        strcpy(real_message[i].name, messages[j].name);
                        strcpy(real_message[i].CAN, messageList[i].channel);
                        strcpy(real_message[i].trans, messageList[i].transmit);
                        real_message[i].cycle = messages[j].cycle;
                        real_message[i].num_signals = messageList[i].signalnum;
                        real_message[i].dlc = messages[j].dlc;
                        for(int k = 0; k < messageList[i].signalnum; k++)           //遍历应用层message中的signal
                        {
                            for(int l = 0; l < messages[j].num_signals; l++)        //遍历all dbc中message的signal
                            {
                                if(strcmp(messageList[i].appsignallist.Signalname[k], messages[j].signals[l].sgname) == 0)  //判断如果两者name相同，将相关数据copy到real_message中signal结构体
                                {
                                    strcpy(real_message[i].signals[k].sgname, messageList[i].appsignallist.Signalname[k]);
                                    strcpy(real_message[i].signals[k].factor, messages[j].signals[l].factor);
                                    strcpy(real_message[i].signals[k].offset, messages[j].signals[l].offset);
                                    strcpy(real_message[i].signals[k].min, messages[j].signals[l].min);
                                    strcpy(real_message[i].signals[k].max, messages[j].signals[l].max);
                                    real_message[i].signals[k].startbit = messages[j].signals[l].startbit;
                                    real_message[i].signals[k].length = messages[j].signals[l].length;
                                    real_message[i].signals[k].mode = messages[j].signals[l].mode;
                                    real_message[i].signals[k].val = messages[j].signals[l].val;
                                }
                            }
                        }
                    }
                }
            }else if(strcmp(messageList[i].channel, "PCAN") == 0)                 //PCAN遍历
            {
                for(int j = CCAN_MES_NUM; j < CCAN_MES_NUM +PCAN_MES_NUM - 1; j++)
                {
                    if(strcmp(messageList[i].Messagename, messages[j].name) == 0)
                    {
                        strcpy(real_message[i].id, messages[j].id);
                        strcpy(real_message[i].name, messages[j].name);
                        strcpy(real_message[i].CAN, messageList[i].channel);
                        strcpy(real_message[i].trans, messageList[i].transmit);
                        real_message[i].cycle = messages[j].cycle;
                        real_message[i].num_signals = messageList[i].signalnum;
                        real_message[i].dlc = messages[j].dlc;
                        for(int k = 0; k < messageList[i].signalnum; k++)
                        {
                            for(int l = 0; l < messages[j].num_signals; l++)
                            {
                                if(strcmp(messageList[i].appsignallist.Signalname[k], messages[j].signals[l].sgname) == 0)
                                {
                                    strcpy(real_message[i].signals[k].sgname, messageList[i].appsignallist.Signalname[k]);
                                    strcpy(real_message[i].signals[k].factor, messages[j].signals[l].factor);
                                    strcpy(real_message[i].signals[k].offset, messages[j].signals[l].offset);
                                    strcpy(real_message[i].signals[k].min, messages[j].signals[l].min);
                                    strcpy(real_message[i].signals[k].max, messages[j].signals[l].max);
                                    real_message[i].signals[k].startbit = messages[j].signals[l].startbit;
                                    real_message[i].signals[k].length = messages[j].signals[l].length;
                                    real_message[i].signals[k].mode = messages[j].signals[l].mode;
                                    real_message[i].signals[k].val = messages[j].signals[l].val;
                                }
                            }
                        }
                    }
                }
            }else if(strcmp(messageList[i].channel, "RCAN") == 0)                   //RCAN遍历
            {
                for(int j = PCAN_MES_NUM; j < CCAN_MES_NUM + PCAN_MES_NUM + RCAN_MES_NUM - 1; j++)
                {
                    if(strcmp(messageList[i].Messagename, messages[j].name) == 0)
                    {
                        strcpy(real_message[i].id, messages[j].id);
                        strcpy(real_message[i].name, messages[j].name);
                        strcpy(real_message[i].CAN, messageList[i].channel);
                        strcpy(real_message[i].trans, messageList[i].transmit);
                        real_message[i].cycle = messages[j].cycle;
                        real_message[i].num_signals = messageList[i].signalnum;
                        real_message[i].dlc = messages[j].dlc;
                        for(int k = 0; k < messageList[i].signalnum; k++)
                        {
                            for(int l = 0; l < messages[j].num_signals; l++)
                            {
                                if(strcmp(messageList[i].appsignallist.Signalname[k], messages[j].signals[l].sgname) == 0)
                                {
                                    strcpy(real_message[i].signals[k].sgname, messageList[i].appsignallist.Signalname[k]);
                                    strcpy(real_message[i].signals[k].factor, messages[j].signals[l].factor);
                                    strcpy(real_message[i].signals[k].offset, messages[j].signals[l].offset);
                                    strcpy(real_message[i].signals[k].min, messages[j].signals[l].min);
                                    strcpy(real_message[i].signals[k].max, messages[j].signals[l].max);
                                    real_message[i].signals[k].startbit = messages[j].signals[l].startbit;
                                    real_message[i].signals[k].length = messages[j].signals[l].length;
                                    real_message[i].signals[k].mode = messages[j].signals[l].mode;
                                    real_message[i].signals[k].val = messages[j].signals[l].val;
                                }
                            }
                        }
                    }
                }
            }else if(strcmp(messageList[i].channel, "RDCAN") == 0)                 //RDCAN遍历
            {
                for(int j = RCAN_MES_NUM; j < CCAN_MES_NUM + PCAN_MES_NUM + RCAN_MES_NUM + RDCAN_MES_NUM - 1; j++)
                {
                    if(strcmp(messageList[i].Messagename, messages[j].name) == 0)
                    {
                        strcpy(real_message[i].id, messages[j].id);
                        strcpy(real_message[i].name, messages[j].name);
                        strcpy(real_message[i].CAN, messageList[i].channel);
                        strcpy(real_message[i].trans, messageList[i].transmit);
                        real_message[i].cycle = messages[j].cycle;
                        real_message[i].num_signals = messageList[i].signalnum;
                        real_message[i].dlc = messages[j].dlc;
                        for(int k = 0; k < messageList[i].signalnum; k++)
                        {
                            for(int l = 0; l < messages[j].num_signals; l++)
                            {
                                if(strcmp(messageList[i].appsignallist.Signalname[k], messages[j].signals[l].sgname) == 0)
                                {
                                    strcpy(real_message[i].signals[k].sgname, messageList[i].appsignallist.Signalname[k]);
                                    strcpy(real_message[i].signals[k].factor, messages[j].signals[l].factor);
                                    strcpy(real_message[i].signals[k].offset, messages[j].signals[l].offset);
                                    strcpy(real_message[i].signals[k].min, messages[j].signals[l].min);
                                    strcpy(real_message[i].signals[k].max, messages[j].signals[l].max);
                                    real_message[i].signals[k].startbit = messages[j].signals[l].startbit;
                                    real_message[i].signals[k].length = messages[j].signals[l].length;
                                    real_message[i].signals[k].mode = messages[j].signals[l].mode;
                                    real_message[i].signals[k].val = messages[j].signals[l].val;
                                }
                            }
                        }
                    }
                }
            }
        }else if(i > (APP_NUM - APP_EQ_NUM - 1))                   //EQCAN遍历
        {
            static int num = -1;
            num++;
            if(strncmp(EQ_messageList[num].channel, "EQCAN", 5) == 0)                   //EQCAN遍历
            {
                for(int j = CCAN_MES_NUM + PCAN_MES_NUM + RCAN_MES_NUM + RDCAN_MES_NUM; j < CCAN_MES_NUM + PCAN_MES_NUM + RCAN_MES_NUM + RDCAN_MES_NUM + EQCAN_MES_NUM; j++)
                {
                    if(strcmp(EQ_messageList[num].Messagename, messages[j].name) == 0)
                    {
                        strcpy(real_message[i].id, messages[j].id);
                        strcpy(real_message[i].name, messages[j].name);
                        strcpy(real_message[i].CAN, EQ_messageList[num].channel);
                        strcpy(real_message[i].trans, EQ_messageList[num].transmit);
                        real_message[i].cycle = messages[j].cycle;
                        real_message[i].num_signals = EQ_messageList[num].signalnum;
                        real_message[i].dlc = messages[j].dlc;
                        for(int k = 0; k < EQ_messageList[num].signalnum; k++)
                        {
                            for(int l = 0; l < messages[j].num_signals; l++)
                            {
                                if(strcmp(EQ_messageList[num].appsignallist.Signalname[k], messages[j].signals[l].sgname) == 0)
                                {
                                    strcpy(real_message[i].signals[k].sgname, EQ_messageList[num].appsignallist.Signalname[k]);
                                    strcpy(real_message[i].signals[k].factor, messages[j].signals[l].factor);
                                    strcpy(real_message[i].signals[k].offset, messages[j].signals[l].offset);
                                    strcpy(real_message[i].signals[k].min, messages[j].signals[l].min);
                                    strcpy(real_message[i].signals[k].max, messages[j].signals[l].max);
                                    real_message[i].signals[k].startbit = messages[j].signals[l].startbit;
                                    real_message[i].signals[k].length = messages[j].signals[l].length;
                                    real_message[i].signals[k].mode = messages[j].signals[l].mode;
                                    real_message[i].signals[k].val = messages[j].signals[l].val;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //------------------------至此，所有需要的DBC信息都已提取，存放在real_message结构体
    //处理EQ中value_type特殊部分
    FILE* file1 = fopen(dbc_filepath[4], "r");
    if (file1 == NULL) {
        printf("Failed to open file: %s\n", dbc_filepath[4]);
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, file1) != NULL) {
        if(strncmp(line, "SIG_VALTYPE_ ", 13) == 0){
            memset(signal_valuetype_name, 0, sizeof(signal_valuetype_name));
            signal_valuetype = 0;
            sscanf(line, "SIG_VALTYPE_ %*d %s : %d;", signal_valuetype_name, &signal_valuetype);
            if(signal_valuetype == 1){
                signal_valuetype = 2;
            }else if(signal_valuetype == 2){
                signal_valuetype = 3;
            }
            for(int value_cycle = 0; value_cycle < APP_NUM; value_cycle++){
                for(int signal_value_cycle = 0; signal_value_cycle < real_message[value_cycle].num_signals; signal_value_cycle++){
                    if(strcmp(real_message[value_cycle].signals[signal_value_cycle].sgname, signal_valuetype_name) == 0){
                        real_message[value_cycle].signals[signal_value_cycle].val = signal_valuetype;
                    }
                }
            }
        }
    }

    //处理cycle time，rx message有些超出范围，将无用的rx cycle设为0
    for(uint8_t i = 0; i < APP_NUM; i++){
        if(strncmp(real_message[i].trans, "Rx", 2) == 0)
        {
            real_message[i].cycle = 0;
        }
    }

    //读取j1939和eq CAN的最大signal数量
    for(int i = 0; i < APP_NUM; i++)
    {
        if(i < (APP_NUM - APP_EQ_NUM))
        {
            if(j1939can_maxsignal_num < real_message[i].num_signals)
            {
                j1939can_maxsignal_num = real_message[i].num_signals;
            }
        }else{
            if(eqcan_maxsignal_num < real_message[i].num_signals)
            {
                eqcan_maxsignal_num = real_message[i].num_signals;
            }
        }
    }

    //H文件输出
    fp = fopen("dbc_database.h", "w");
    if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
    }
    dbc_databaseh_title_add(fp, app_ccan_num, app_pcan_num, app_rcan_num, app_rdcan_num, app_eqcan_num, j1939can_maxsignal_num, eqcan_maxsignal_num);

    //C文件输出
    fp = fopen("dbc_database.c", "w");
    if (fp == NULL) {
    printf("Failed to open file\n");
    return 1;
    }
    dbc_databasec_title_add(fp);
    dbc_databasec_CAN_t_value_add(fp);
    dbc_databasec_CAN_t_const_add(fp, app_ccan_num, app_pcan_num, app_rcan_num, app_rdcan_num, app_eqcan_num, real_message);
    dbc_databasec_end_add(fp);
    free(messages);
    return 0;
}