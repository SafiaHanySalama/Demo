import unittest
import serial
import time
import switch_pb2
import switch_pb2

class TestMicrocontroller(unittest.TestCase):
    def setUp(self):
                # Define serial port settings for your microcontroller
                self.SERIAL_PORT = 'COM5'  # Update with your serial port
                self.BAUD_RATE = 115200  # Update with your baud rate
                self.ser = serial.Serial(self.SERIAL_PORT, self.BAUD_RATE, timeout=1)
    
    def test_switch_pressed_led_on(self):
                #create a SetSwitchRequest message to get the sate of the switch
                switch_response = switch_pb2.SwitchStatusResponse()

                # Receive the response from the microcontroller
                switch_response.switch_state = self.ser.read(1)

                # Create a SetLEDRequest message to turn on the LED
                led_request = switch_pb2.LedControlRequest()
                led_request.led_state = switch_response.switch_state #"0"

                # Send the LED control request to microcontroller
                self.ser.write(led_request.led_state[0].encode())
                
                # Receive the response from the microcontroller
                response = self.ser.read(1)

                # Check the acknowledgment
                self.assertEqual(response, switch_response.switch_state[0].encode())

    def tearDown(self):
                # Close serial port
                self.ser.close()

if __name__ == '__main__':
     unittest.main()

       