import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JTextField text;
	private JButton login, view;
	private JLabel instructions;
	 
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
	}//end Tile constructor
	private class ButtonsListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if(e.getSource()==login)
			{
				String pass= text.getText();
				/**use JNA to make call to syscall 289, getlevel*/
				/**Go to UserPanel if password matches primary user's*/
				/**Go to ViewPanel if password matches other user*/
				/**set current access level to the one returned by the syscall*/
				/**Stay and tell user to try again if the password is wrong, implement this if there is time only*/
			}//end if statement
			else
			{
				/**Go to ViewPanel if password matches other user, or view was clicked*/
				/**set current access level to 4*/
			}//end else statement
		}//end ActionPerformed method
	}//end ButtonsListener class
}//end LoginPanel class
