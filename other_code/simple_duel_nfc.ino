
 /*
 * Started with public domain code found at : http://playground.arduino.cc/Learning/MFRC522
 *
 * Modified by Benjamin Haos for easier readability and duel NFC reader.
 *
 * Pin layout should be as follows:
 * NFC			Arduino		Wire
 * Reader		Uno			Color
 * Pin			Pin
 * ------------------------------------------------------------
 * 			[NFC One]
 * RST			9			White
 * SDA			10			Grey

 * 			[NFC Two]
 * RST			5			White
 * SDA			6			Grey

 * 			[Both NFC]
 * MISO			12			Purple
 * MOSI			11			Blue
 * SCK			13			Green
 *
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SS_PIN_1 10
MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1);	// Create MFRC522 instance 1.

#define RST_PIN_2 5
#define SS_PIN_2 6
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2);	// Create MFRC522 instance 2.

int hello_delay = 500;

int count_times_read = 0;
int max_count_before_reset = 100;

float manually_set_threshold_to_activate = 0.40;

void say_hello()
{
	//Serial.println("Hello from hello function!");
}

void setup_nfc()
{
	SPI.begin();			// Init SPI bus
	mfrc522_1.PCD_Init();	// Init NFC card reader one.
	mfrc522_2.PCD_Init();	// Init NFC card reader two.

}

int num_times_to_cycle_nfc = 10;

void do_activity_done_when_device_senses_activity_be_done_has_been_requested()
{
	String found_serial_one = "";
	String found_serial_two = "";

	mfrc522_1.PCD_Init();	// Init NFC card reader one.
	mfrc522_2.PCD_Init();	// Init NFC card reader two.


	for (int i = 0; i < num_times_to_cycle_nfc; i++ )
	{
		if ( mfrc522_1.PICC_IsNewCardPresent()  )
		{
			Serial.print(" - reader 1 noticed new card, value = ");
			if( mfrc522_1.PICC_ReadCardSerial() )
			{
				mfrc522_2.PICC_HaltA();
				found_serial_one = getCardValue(mfrc522_1.uid.uidByte, mfrc522_1.uid.size);
				//mfrc522_1.PICC_HaltA();
			}
			Serial.println("" + String(found_serial_one)); 
		}

		if ( mfrc522_2.PICC_IsNewCardPresent() )
		{
			Serial.print(" - reader 2 noticed new card, value = ");
			if( mfrc522_2.PICC_ReadCardSerial() )
			{
				mfrc522_1.PICC_HaltA();
				found_serial_two = getCardValue(mfrc522_2.uid.uidByte, mfrc522_2.uid.size);
				//mfrc522_2.PICC_HaltA();
			}
			Serial.println("" + String(found_serial_two)); 
		}
	}
}

String getCardValue(byte *buffer, byte bufferSize)
{
	String return_String = "";
	for (byte i = 0; i < bufferSize; i++)
	{
		if (buffer[i] < 100)
		{
			return_String += "0";
		}
		if (buffer[i] < 10)
		{
			return_String += "0";
		}
		return_String += String(buffer[i]);
	}
	return return_String;
}

void setup()
{
	say_hello();
	setup_nfc();
	Serial.begin(9600);
	Serial.println("Setep complete...");
}

void loop()
{
	// ToDo : Add wait or signal to  do below.
	do_activity_done_when_device_senses_activity_be_done_has_been_requested();
}
