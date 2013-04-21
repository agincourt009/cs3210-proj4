import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UserPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JButton logout, view, add, addrelation;
	private JLabel instructions;
	private MainPanel panel;
	 
	public UserPanel(MainPanel panel)
	{
		this.panel = panel;
		instructions = new JLabel("Would you like to view photos, add photos,\nadd friends or family, or logout?");
		
		logout = new JButton("Logout");
		
		view = new JButton("View Photos");
		
		add = new JButton("Add Photos");
		
		addrelation = new JButton("Add Friends or Family");
		
		
		setPreferredSize(new Dimension(400,400));
		
		ButtonListener log = new ButtonListener();
		logout.addActionListener(log);
		
		ButtonListener viewpho = new ButtonListener();
		view.addActionListener(viewpho);
		
		ButtonListener addpho = new ButtonListener();
		add.addActionListener(addpho);
		
		ButtonListener addf = new ButtonListener();
		addrelation.addActionListener(addf);
		
		add(instructions);
		add(view);
		add(add);
		add(addrelation);
		add(logout);
	}//end UserPanel constructor
	
	public void setPanel(MainPanel panel)
	{
		this.panel = panel;
	}//end setPanel method
	
	private class ButtonListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if(e.getSource()==logout)
			{
				panel.logout();
			}//end if statement
			else if(e.getSource()==add)
			{
				panel.switchAdd();
			}//end else statement
			else if(e.getSource()==addrelation)
			{
				panel.switchRelationship();
			}//end else if statement
			else
			{
				panel.switchView(false);
			}
		}//end ActionPerformed method
	}//end ButtonListener class
}//end UserPanel class
