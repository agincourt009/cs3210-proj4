import javax.swing.*;
import com.sun.jna.Library;
import com.sun.jna.Native;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FirstPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JTextField text1, text2, text3;
	private JButton done;
	private JLabel instructions;
	private MainPanel panel;
	 
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
	}//end FirstPanel constructor
	
	public void setPanel(MainPanel panel)
	{
		this.panel = panel;
	}//end setPanel method
	
	public interface CStdLib extends Library 
	{
        int syscall(int number, Object... args);
    }//end CStdLib interface
	
	private class DoneListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			CStdLib c = (CStdLib)Native.loadLibrary("c", CStdLib.class);
			String pass1= text1.getText();
			c.syscall(290, pass1);
			String pass2= text2.getText();
			c.syscall(290, pass2);
			String pass3= text3.getText();
			c.syscall(290, pass3);
			panel.switchUser();
			panel.setCurlevel(1);
		}//end ActionPerformed method
	}//end DoneListener class
}//end FirstPanel class
