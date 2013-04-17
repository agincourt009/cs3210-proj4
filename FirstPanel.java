import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FirstPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JTextField text1, text2, text3;
	private JButton done;
	private JLabel instructions;
	 
	public FirstPanel()
	{
		instructions = new JLabel("Please choose a password for each privacy level.");
		
		text1 = new JTextField("Password for your access");
		text2 = new JTextField("Password for friend's access");
		text3 = new JTextField("Password for family's access");
		
		done = new JButton("Done");
		
		setPreferredSize(new Dimension(400,400));
		
		DoneListener don = new DoneListener();
		done.addActionListener(don);
		
		add(instructions);
		add(text1);
		add(text2);
		add(text3);
		add(done);
	}//end Tile constructor
	private class DoneListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			String pass1= text1.getText();
			/**use JNA to make call to syscall 288, setpassword*/
			String pass2= text2.getText();
			/**use JNA to make call to syscall 288, setpassword*/
			String pass3= text3.getText();
			/**use JNA to make call to syscall 288, setpassword*/
			/**Go to UserPanel*/
			/**set current access level to one*/
		}//end ActionPerformed method
	}//end DoneListener class
}//end FirstPanel class
