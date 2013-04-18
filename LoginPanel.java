import javax.swing.*;
import com.sun.jna.Library;
import com.sun.jna.Native;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JTextField text;
	private JButton login, view;
	private JLabel instructions;
	private MainPanel panel;
	 
	public LoginPanel()
	{
		instructions = new JLabel("Either enter the password for your access level,\nor click the 'Open Access' button to view the photos\nthat are accessible by everyone.");
		
		text = new JTextField("Password"); 
		
		login = new JButton("Login");
		
		view = new JButton("Open Access");
		
		setPreferredSize(new Dimension(400,400));
		
		ButtonsListener log = new ButtonsListener();
		login.addActionListener(log);
		
		ButtonsListener opac = new ButtonsListener();
		view.addActionListener(opac);
		
		add(instructions);
		add(text);
		add(login);
		add(view);
	}//end LoginPanel constructor
	
	public void setPanel(MainPanel panel)
	{
		this.panel = panel;
	}//end setPanel method
	
	public interface CStdLib extends Library 
	{
        int syscall(int number, Object... args);
    }//end CStdLib interface
	
	private class ButtonsListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if(e.getSource()==login)
			{
				CStdLib c = (CStdLib)Native.loadLibrary("c", CStdLib.class);
				String pass= text.getText();
				int level = c.syscall(290, pass);
				if(level == 1)
				{
					panel.setCurlevel(1);
					panel.switchUser();
				}//end else if statement
				else if(level == 2)
				{
					panel.setCurlevel(2);
					panel.switchView();
				}//end else if statement
				else if(level==3)
				{
					panel.setCurlevel(3);
					panel.switchView();
				}//end else if statement
				else
				{
					JOptionPane.showMessageDialog(panel, "The password entered does not match any for the system.\nPlease try again.");
					panel.logout();
				}//end else statement
			}//end if statement
			else
			{
				panel.setCurlevel(4);
				panel.switchView();
			}//end else statement
		}//end ActionPerformed method
	}//end ButtonsListener class
}//end LoginPanel class
