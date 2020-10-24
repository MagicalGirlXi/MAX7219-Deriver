#define LED_MATRIX_SS 10

#define SPI_OUT 11
#define SPI_CLK 13

//define the register addr of MAX7219
#define MATRIX_DECODE_MODE 0x09
#define MATRIX_INTENSITY 0x0A
#define MATRIX_SCAN_LIMIT 0x0B
#define MATRIX_SHUTDOWN 0x0C
#define MATRIX_DISPLAY_TEST 0x0F

uint8_t turn_left[8] = {0x0,0x20,0x60,0xFF,0xFF,0x60,0x20,0x0};
uint8_t turn_right[8] = {0x0,0x4,0x6,0xFF,0xFF,0x6,0x4,0x0};
uint8_t turn_forword[8] = {0x18,0x3C,0x7E,0x18,0x18,0x18,0x18,0x18};
uint8_t turn_back[8] = {0x18,0x18,0x18,0x18,0x18,0x7E,0x3C,0x18};


struct MatrixInitial
{
    uint8_t RegAddr;
    uint8_t RegValue;
};
void setup()
{
    Serial.begin(9600);
    pinMode(LED_MATRIX_SS, OUTPUT);
    pinMode(SPI_OUT, OUTPUT);
    pinMode(SPI_CLK, OUTPUT);
    digitalWrite(LED_MATRIX_SS, HIGH);
    //SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    initialMatrix();
    Serial.println("MAX7219 initialed!");
}

void Write7219(unsigned char address, unsigned char dat)
{
    char i;
    digitalWrite(LED_MATRIX_SS, LOW); //拉低片选线，选中器件
    //发送地址
    for (i = 7; i >= 0; i--) //移位循环8次
    {
        digitalWrite(SPI_CLK, LOW);                   //清零时钟总线
        digitalWrite(SPI_OUT, bitRead(address, i)); //每次取高字节
        //Serial.print(bitRead(address, i));
        digitalWrite(SPI_CLK, HIGH); //时钟上升沿，发送地址
    }

    //Serial.print('-');
    //发送地址
    for (i = 7; i >= 0; i--) //移位循环8次
    {
        digitalWrite(SPI_CLK, LOW);               //清零时钟总线
        digitalWrite(SPI_OUT, bitRead(dat, i)); //每次取高字节
        //Serial.print(bitRead(dat, i));
        digitalWrite(SPI_CLK, HIGH); //时钟上升沿，发送地址
    }
    //Serial.println("");
    digitalWrite(LED_MATRIX_SS, HIGH); //发送结束，上升沿锁存数据
}

void initialMatrix()
{
    Write7219(MATRIX_SHUTDOWN, 0x01);    //开启正常工作模式（0xX1）
    Write7219(MATRIX_DISPLAY_TEST, 0x00); //选择工作模式（0xX0）
    Write7219(MATRIX_DECODE_MODE, 0x00);  //选用全译码模式
    Write7219(MATRIX_SCAN_LIMIT, 0x07);   //8只LED全用
    Write7219(MATRIX_INTENSITY, 0x04);    //设置初始亮度
}

void Display(uint8_t *in)
{
    for (byte i = 1; i <= 8; i++)
    {
        Write7219(i,in[i-1]);
    }
}

void loop()
{
    Display(turn_left);
    delay(2000);
    Display(turn_right);
    delay(2000);
    Display(turn_forword);
    delay(2000);
    Display(turn_back);
    delay(2000);
}
