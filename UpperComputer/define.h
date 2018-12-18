


// 服务器指令解析定义
#define SERVERCMD_RECORD     0x100       //服务器指令：注册确认
// #define SERVERCMD_RESPONSE   0x101       //服务器指令：心跳应答
#define SERVERCMD_READY      0x102       //服务器指令：准备
#define SERVERCMD_LOAD       0x103       //服务器指令：烧录
#define SERVERCMD_DATA       0x105       //服务器指令：数据传输
#define SERVERCMD_TEST       0x106       //服务器指令：自动测试
#define SERVERCMD_STARTTEST  0x107       //服务器指令：启动自动测试
#define SERVERCMD_ENDTEST    0x108       //服务器指令：停止自动测试
#define SERVERCMD_BREAK      0x109       //服务器指令：断开连接
//#define SERVERCMD_VGASTART   0x10a     //服务器指令：发送vga图像数据
//#define SERVERCMD_VGASTOP    0x10b     //服务器指令：发送vga图像数据
#define SERVERCMD_EXPCOMSET  0x10c       //服务器指令：实验串口设置
#define SERVERCMD_EXPCOMSENDDATA  0x10d  //服务器指令：实验串口发送数据
#define SERVERCMD_PS2SENDDATA 0x10e      //服务器指令：PS2发送数据
#define SERVERCMD_ASKSTATE 0x10f         //服务器指令：查询上位机状态


// 定时器ID
#define TIMERID_REGISTER     100       //注册定时器
#define TIMERID_DATA_SAMPLE  102       //数据采集定时器
#define TIMERID_TEST_DATA_SAMPLE  103       //自动测试数据采集定时器
#define TIMERID_FILEREV      105       //文件接收超时定时器
#define TIMERID_EXPCOMRX     106       //实验串口接收定时器
#define TIMERID_SPI_FLASH_CHIP_ERASE 107       //spi-flash 整片擦除定时器
//#define TIMERID_VGA_SAMPLE   108       //VGA图像采集定时器
#define TIMERID_HARDWARE_TEST   109     //硬件自检定时器
#define TIMERID_JTAG_TIMEOUT   110     //jtag加载超时定时器
#define TIMERID_CHECK_CONNECT 111  //检测断网 


// 定时器时间
#define TIMERID_REGISTER_TIME     5*60*1000   //注册定时器时间，5分钟，单位：ms
//#define TIMERID_REGISTER_TIME     10*1000     //注册定时器时间，60秒，单位：ms
#define TIMERID_DATA_SAMPLE_TIME  100      //数据采集定时器时间，100毫秒，单位：ms
#define TIMERID_TEST_DATA_SAMPLE_TIME  500      //自动测试数据采集定时器时间，500毫秒，单位：ms
#define TIMERID_FILEREV_TIME      5*60*1000  //文件接收超时定时器时间，5分钟，单位：ms
#define TIMERID_EXPCOMRX_TIME     1*1000     //实验串口接收定时器时间，1秒，单位：ms
#define TIMERID_SPI_FLASH_CHIP_ERASE_TIME 10*1000       //spi-flash 整片擦除定时器时间，10秒，单位：ms
//#define TIMERID_VGA_SAMPLE_TIME   100       //VGA图像采集定时器时间，100毫秒，单位：ms
#define TIMERID_HARDWARE_TEST_TIME   500      //硬件自检定时器时间，500毫秒，单位：ms
#define TIMERID_JTAG_TIMEOUT_TIME   60*1000   //jtag加载超时定时器时间，60秒，单位：ms
#define TIMERID_CHECK_CONNECT_TIME 20*1000 // 20s检测断网间隔



// 主控串口参数定义
//#define COM_PORT_BAUDRATE 2000000
#define COM_PORT_BAUDRATE 8000000
//#define COM_PORT_BAUDRATE 115200 //// 
#define COM_PORT_DATABIT 8       //// Number of bits/byte, 4-8
#define COM_PORT_STOPBIT 0       //// 0,1,2 = 1, 1.5, 2
#define COM_PORT_PARITYBIT 0     //// 0-4 = None,Odd,Even,Mark,Space
#define COMBUFSIZE 64*1024      // 缓存大小
#define FPGA_READ_TIMEOUT 5000 // 5000 times to read status


// 实验串口参数定义
#define EXPCOM_PORT_BAUDRATE 1000000
#define EXPCOM_PORT_DATABIT 8       //// Number of bits/byte, 4-8
#define EXPCOM_PORT_STOPBIT 0       //// 0,1,2 = 1, 1.5, 2
#define EXPCOM_PORT_PARITYBIT 0     //// 0-4 = None,Odd,Even,Mark,Space
#define EXPCOM_CLK_FREQ 100000000
#define EXPCOMBUFSIZE 8*1024






// FPGA升级参数定义
#define FPGA_UPDATE_START_ADDR 0x00000  // 配置文件在spi-flash内的起始地址
#define FPGA_UPDATE_MODE_LOCAL 0x0  // FPGA升级模式：本地
#define FPGA_UPDATE_MODE_ONLINE 0x1  // FPGA升级模式：在线
// bit文件有效数据起始位置，每个器件的不一样
#define BIT_START_ADDR_XC6SLX100 0x63
#define BIT_START_ADDR_XC6SLX16 0x76
// jtag 参数定义
#define JTAG_BLOCK_WRITE_LENGTH 16*1024 //  bytes


// 硬件自检参数定义
#define HWT_JTAG_TIMEOUT 120 //  60秒，单位：500ms
#define HWT_EXPCOM_TIMEOUT 2 //  1秒，单位：500ms
#define HWT_PS2_TIMEOUT 120 //  60秒，单位：500ms
#define HWT_CLK_1KHZ_OFFSET_P 1000 + 10
#define HWT_CLK_1KHZ_OFFSET_N 1000 - 10
#define HWT_CLK_750KHZ_OFFSET_P 750000 + 100
#define HWT_CLK_750KHZ_OFFSET_N 750000 - 100
#define HWT_CLK_12MHZ_OFFSET_P 12000000 + (12000000 * 50 / 1000000)
#define HWT_CLK_12MHZ_OFFSET_N 12000000 - (12000000 * 50 / 1000000)




