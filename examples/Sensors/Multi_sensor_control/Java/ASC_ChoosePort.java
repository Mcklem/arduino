import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;

import com.fazecast.jSerialComm.SerialPort;

import engine.Core;

import javax.swing.JButton;
import java.awt.Color;


public class ASC_ChoosePort extends Core {

	public ASC_ChoosePort() {
		this.setTicks(60D);
		initialize();
		this.start();
	}
	
	private void initialize(){
		frame = new JFrame();
		frame.setResizable(false);
		frame.getContentPane().setForeground(Color.BLACK);
		frame.setVisible(true);
		frame.setBounds(100, 100, 570, 387);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
	}
	
	protected void update() {
		super.update();
	}
	
	protected void draw(){
		SerialPort[] ports = SerialPort.getCommPorts();
		System.out.println(ports.length);
		new ASC_Display(ports[0]);
		destroy();
	}
}
	