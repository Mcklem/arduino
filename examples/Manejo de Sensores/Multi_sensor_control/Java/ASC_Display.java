
import java.util.Scanner;
import javax.swing.JFrame;
import engine.Core;
import javax.swing.JLabel;

import com.fazecast.jSerialComm.SerialPort;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.awt.event.ActionEvent;

public class ASC_Display {

	private JFrame frame;
	private SerialPort serialPort;
	private JTextField textField;

	public ASC_Display(SerialPort serialPort) {
		this.serialPort = serialPort;
		initialize();
	}

	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 566, 382);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		JLabel lblLdr = new JLabel("Light:");
		lblLdr.setBounds(75, 36, 85, 14);
		frame.getContentPane().add(lblLdr);
		
		JLabel lblLdrval = new JLabel("ldr_val");
		lblLdrval.setBounds(210, 36, 46, 14);
		frame.getContentPane().add(lblLdrval);
		
		JLabel lblDistance = new JLabel("Distance:");
		lblDistance.setBounds(75, 71, 85, 14);
		frame.getContentPane().add(lblDistance);
		
		JLabel lblDistval = new JLabel("dist_val");
		lblDistval.setBounds(210, 71, 46, 14);
		frame.getContentPane().add(lblDistval);
		
		JLabel lblTemperature = new JLabel("Temperature:");
		lblTemperature.setBounds(75, 110, 85, 14);
		frame.getContentPane().add(lblTemperature);
		
		JLabel lblTempval = new JLabel("temp_val");
		lblTempval.setBounds(210, 110, 46, 14);
		frame.getContentPane().add(lblTempval);
		
		JLabel lblHumidity = new JLabel("Humidity:");
		lblHumidity.setBounds(75, 150, 85, 14);
		frame.getContentPane().add(lblHumidity);
		
		JLabel lblHumidityval = new JLabel("humidity_val");
		lblHumidityval.setBounds(210, 150, 46, 14);
		frame.getContentPane().add(lblHumidityval);
		
		textField = new JTextField();
		textField.setBounds(75, 268, 134, 20);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		if(serialPort.openPort()){
			System.out.println("Succesfully opened");
		}
		else {
			System.out.println("Error abriendo el puerto " + serialPort.getDescriptivePortName());
			return;
		}
		serialPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
		serialPort.setBaudRate(9600);
		
		JButton btnSend = new JButton("Send");
		btnSend.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				OutputStream os = serialPort.getOutputStream();
				DataOutputStream dos = new DataOutputStream(os);
				try {
					dos.writeUTF(textField.getText() + " /r");
					dos.flush();
				} 
				catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		btnSend.setBounds(330, 267, 89, 23);
		frame.getContentPane().add(btnSend);
		
		JLabel lblRam = new JLabel("RAM:");
		lblRam.setBounds(357, 36, 85, 14);
		frame.getContentPane().add(lblRam);
		
		JLabel lblRamval = new JLabel("RAM_val");
		lblRamval.setBounds(413, 36, 85, 14);
		frame.getContentPane().add(lblRamval);
		
		JLabel lblLed = new JLabel("LED:");
		lblLed.setBounds(357, 71, 46, 14);
		frame.getContentPane().add(lblLed);
		
		JLabel lblRgbval = new JLabel("RGB_val");
		lblRgbval.setBounds(413, 71, 127, 14);
		frame.getContentPane().add(lblRgbval);
		frame.setVisible(true);
		
		Scanner scanner = new Scanner(serialPort.getInputStream());
	
		int serialDataIndex = 0;
		while(scanner.hasNextLine()){
			
			String[] data = scanner.nextLine().split(",");
			
			if(data.length==8){
				lblLdrval.setText(data[0]);
				lblDistval.setText(data[1] + " cm");
				lblTempval.setText(data[2] + " ºC");
				lblHumidityval.setText(data[3] + " %");
				lblRamval.setText(data[4] + " KB");
				lblRgbval.setText("R(" + data[5] + ") G(" + data[6] + ")B (" + data[7] + ")");
			}
			else{
				for(String d : data){
					System.out.println(d);
					//Show ascii values of received message
					/* char[] dr = d.toCharArray();
					for(char dru : dr){
						System.out.println((int) dru);
					}*/
				}
			}
		}
		System.out.println("end");	
	}
}
