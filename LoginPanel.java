import javax.swing.*;
import com.sun.jna.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JTextField text, user;
	private JButton login, view, create;
	private JLabel instructions;
	private MainPanel panel;
	 
	public LoginPanel()
	{
		instructions = new JLabel("Enter your username and password to login, create a new\naccount,or click the 'View Public' button to view public photos.");
		
		text = new JTextField("Password"); 
		user = new JTextField("Username");
		
		login = new JButton("Login");
		view = new JButton("Open Access");
		create = new JButton("Create Account");
		
		setPreferredSize(new Dimension(400,400));
		
		ButtonsListener log = new ButtonsListener();
		login.addActionListener(log);
		
		ButtonsListener opac = new ButtonsListener();
		view.addActionListener(opac);
		
		ButtonsListener creat = new ButtonsListener();
		create.addActionListener(creat);
		
		add(instructions);
		add(user);
		add(text);
		add(login);
		add(create);
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
				String usern = user.getText();
				
				Memory passmem = new Memory(pass.length());
				passmem.write(0, pass.getBytes(), 0, pass.length());
				
				Memory usermem = new Memory(usern.length());
				usermem.write(0, usern.getBytes(), 0, usern.length());
				
				int passlength = Native.toCharArray(pass).length;
				int userlength = Native.toCharArray(usern).length;
				
				int correct = c.syscall(286, usermem, passmem,userlength, passlength);
				if(correct == 1)
				{
					User newu = new User(usern);
					panel.setCurlevel(0);
					panel.setCurUser(newu);
					panel.switchUser();
				}//end else if statement
				else
				{
					JOptionPane.showMessageDialog(panel, "The username and password entered do not match.\nPlease try again.");
					panel.logout();
				}//end else statement
			}//end if statement
			else if(e.getSource()==create)
			{
				panel.switchNew();
			}//end else if statement
			else
			{
				panel.setCurlevel(4);
				panel.switchView();
			}//end else statement
		}//end ActionPerformed method
	}//end ButtonsListener class
}//end LoginPanel class
