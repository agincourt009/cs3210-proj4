import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
	
public class ViewPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JButton logout;
	private JLabel instructions;
	private JSpinner photos;
	 
	public ViewPanel()
	{	
		instructions = new JLabel("Please first select a privacy level for the photo,\nand then click the 'Choose Photo' button to select\na photo to add.");
		
		logout = new JButton("Logout");
		
		setPreferredSize(new Dimension(400,400));
		
		RadioListener log = new RadioListener();
		logout.addActionListener(log);
		
		add(instructions);
		add(logout);
	}//end Tile constructor
	private class RadioListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if(e.getSource()==logout)
			{
				/**Call main panel's logout method*/
			}//end if statement
			else if(e.getSource()==view)
			{
				/**Go to ViewPanel*/
			}
			else
			{
				int returnVal = chooser.showOpenDialog(chooseframe);
			    if(returnVal == JFileChooser.APPROVE_OPTION) 
			    {
			    	/**Add file to the FileSystem*/
			       System.out.println("The File has been added. Please add another file or logout.");
			    }//end if statement
			  /**Go back to AddPanel*/
			}//end else statement
		}//end ActionPerformed method
	}//end ButtonListener class
}//end ViewPanel class


