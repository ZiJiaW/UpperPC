


// ������ָ���������
#define SERVERCMD_RECORD     0x100       //������ָ�ע��ȷ��
// #define SERVERCMD_RESPONSE   0x101       //������ָ�����Ӧ��
#define SERVERCMD_READY      0x102       //������ָ�׼��
#define SERVERCMD_LOAD       0x103       //������ָ���¼
#define SERVERCMD_DATA       0x105       //������ָ����ݴ���
#define SERVERCMD_TEST       0x106       //������ָ��Զ�����
#define SERVERCMD_STARTTEST  0x107       //������ָ������Զ�����
#define SERVERCMD_ENDTEST    0x108       //������ָ�ֹͣ�Զ�����
#define SERVERCMD_BREAK      0x109       //������ָ��Ͽ�����
//#define SERVERCMD_VGASTART   0x10a     //������ָ�����vgaͼ������
//#define SERVERCMD_VGASTOP    0x10b     //������ָ�����vgaͼ������
#define SERVERCMD_EXPCOMSET  0x10c       //������ָ�ʵ�鴮������
#define SERVERCMD_EXPCOMSENDDATA  0x10d  //������ָ�ʵ�鴮�ڷ�������
#define SERVERCMD_PS2SENDDATA 0x10e      //������ָ�PS2��������
#define SERVERCMD_ASKSTATE 0x10f         //������ָ���ѯ��λ��״̬


// ��ʱ��ID
#define TIMERID_REGISTER     100       //ע�ᶨʱ��
#define TIMERID_DATA_SAMPLE  102       //���ݲɼ���ʱ��
#define TIMERID_TEST_DATA_SAMPLE  103       //�Զ��������ݲɼ���ʱ��
#define TIMERID_FILEREV      105       //�ļ����ճ�ʱ��ʱ��
#define TIMERID_EXPCOMRX     106       //ʵ�鴮�ڽ��ն�ʱ��
#define TIMERID_SPI_FLASH_CHIP_ERASE 107       //spi-flash ��Ƭ������ʱ��
//#define TIMERID_VGA_SAMPLE   108       //VGAͼ��ɼ���ʱ��
#define TIMERID_HARDWARE_TEST   109     //Ӳ���Լ춨ʱ��
#define TIMERID_JTAG_TIMEOUT   110     //jtag���س�ʱ��ʱ��
#define TIMERID_CHECK_CONNECT 111  //������ 


// ��ʱ��ʱ��
#define TIMERID_REGISTER_TIME     5*60*1000   //ע�ᶨʱ��ʱ�䣬5���ӣ���λ��ms
//#define TIMERID_REGISTER_TIME     10*1000     //ע�ᶨʱ��ʱ�䣬60�룬��λ��ms
#define TIMERID_DATA_SAMPLE_TIME  100      //���ݲɼ���ʱ��ʱ�䣬100���룬��λ��ms
#define TIMERID_TEST_DATA_SAMPLE_TIME  500      //�Զ��������ݲɼ���ʱ��ʱ�䣬500���룬��λ��ms
#define TIMERID_FILEREV_TIME      5*60*1000  //�ļ����ճ�ʱ��ʱ��ʱ�䣬5���ӣ���λ��ms
#define TIMERID_EXPCOMRX_TIME     1*1000     //ʵ�鴮�ڽ��ն�ʱ��ʱ�䣬1�룬��λ��ms
#define TIMERID_SPI_FLASH_CHIP_ERASE_TIME 10*1000       //spi-flash ��Ƭ������ʱ��ʱ�䣬10�룬��λ��ms
//#define TIMERID_VGA_SAMPLE_TIME   100       //VGAͼ��ɼ���ʱ��ʱ�䣬100���룬��λ��ms
#define TIMERID_HARDWARE_TEST_TIME   500      //Ӳ���Լ춨ʱ��ʱ�䣬500���룬��λ��ms
#define TIMERID_JTAG_TIMEOUT_TIME   60*1000   //jtag���س�ʱ��ʱ��ʱ�䣬60�룬��λ��ms
#define TIMERID_CHECK_CONNECT_TIME 20*1000 // 20s���������



// ���ش��ڲ�������
//#define COM_PORT_BAUDRATE 2000000
#define COM_PORT_BAUDRATE 8000000
//#define COM_PORT_BAUDRATE 115200 //// 
#define COM_PORT_DATABIT 8       //// Number of bits/byte, 4-8
#define COM_PORT_STOPBIT 0       //// 0,1,2 = 1, 1.5, 2
#define COM_PORT_PARITYBIT 0     //// 0-4 = None,Odd,Even,Mark,Space
#define COMBUFSIZE 64*1024      // �����С
#define FPGA_READ_TIMEOUT 5000 // 5000 times to read status


// ʵ�鴮�ڲ�������
#define EXPCOM_PORT_BAUDRATE 1000000
#define EXPCOM_PORT_DATABIT 8       //// Number of bits/byte, 4-8
#define EXPCOM_PORT_STOPBIT 0       //// 0,1,2 = 1, 1.5, 2
#define EXPCOM_PORT_PARITYBIT 0     //// 0-4 = None,Odd,Even,Mark,Space
#define EXPCOM_CLK_FREQ 100000000
#define EXPCOMBUFSIZE 8*1024






// FPGA������������
#define FPGA_UPDATE_START_ADDR 0x00000  // �����ļ���spi-flash�ڵ���ʼ��ַ
#define FPGA_UPDATE_MODE_LOCAL 0x0  // FPGA����ģʽ������
#define FPGA_UPDATE_MODE_ONLINE 0x1  // FPGA����ģʽ������
// bit�ļ���Ч������ʼλ�ã�ÿ�������Ĳ�һ��
#define BIT_START_ADDR_XC6SLX100 0x63
#define BIT_START_ADDR_XC6SLX16 0x76
// jtag ��������
#define JTAG_BLOCK_WRITE_LENGTH 16*1024 //  bytes


// Ӳ���Լ��������
#define HWT_JTAG_TIMEOUT 120 //  60�룬��λ��500ms
#define HWT_EXPCOM_TIMEOUT 2 //  1�룬��λ��500ms
#define HWT_PS2_TIMEOUT 120 //  60�룬��λ��500ms
#define HWT_CLK_1KHZ_OFFSET_P 1000 + 10
#define HWT_CLK_1KHZ_OFFSET_N 1000 - 10
#define HWT_CLK_750KHZ_OFFSET_P 750000 + 100
#define HWT_CLK_750KHZ_OFFSET_N 750000 - 100
#define HWT_CLK_12MHZ_OFFSET_P 12000000 + (12000000 * 50 / 1000000)
#define HWT_CLK_12MHZ_OFFSET_N 12000000 - (12000000 * 50 / 1000000)




