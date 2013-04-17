import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AddPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JButton logout, choose, view;
	private JLabel instructions;
	private ButtonGroup group;
	private JRadioButton level1, level2, level3, level4;
	private int curlevel;
	private JFileChooser chooser;
	private FileNameExtensionFilter filter;
	private JFrame chooseframe;
	 
	public AddPanel()
	{
		chooser = new JFileChooser();
	    filter = new FileNameExtensionFilter("JPG images","jpg");
	    chooser.setFileFilter(filter);
	    
	    chooseframe = new JFrame();
		
		instructions = new JLabel("Please first select a privacy level for the photo,\nand then click the 'Choose Photo' button to select\na photo to add.");
		
		logout = new JButton("Logout");
		
		group = new ButtonGroup();
		
		level1 = new JRadioButton("Level 1: Only Me");
		level1.setSelected(true);
		
		level2 = new JRadioButton("Level 2: Friends and I");
		
		level3 = new JRadioButton("Level 3: Family, Friends and I");
		
		level4 = new JRadioButton("Level 4: Everyone");
		
		group.add(level1);
		group.add(level2);
		group.add(level3);
		group.add(level4);
		
		choose = new JButton("Choose Photo");
		
		view = new JButton("View Photos");
		
		setPreferredSize(new Dimension(400,400));
		
		RadioListener log = new RadioListener();
		logout.addActionListener(log);
		
		RadioListener lev1 = new RadioListener();
		level1.addActionListener(lev1);
		
		RadioListener lev2 = new RadioListener();
		level2.addActionListener(lev2);
		
		RadioListener lev3 = new RadioListener();
		level3.addActionListener(lev3);
		
		RadioListener lev4 = new RadioListener();
		level4.addActionListener(lev4);
		
		RadioListener choice = new RadioListener();
		choose.addActionListener(choice);
		
		RadioListener vie = new RadioListener();
		view.addActionListener(vie);
		
		add(instructions);
		add(level1);
		add(level2);
		add(level3);
		add(level4);
		add(choose);
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
			else if(e.getSource()==level1)
			{
				curlevel = 1;
			}//end else statement
			else if(e.getSource()==level2)
			{
				curlevel = 2;
			}//end else if statement
			else if(e.getSource()==level3)
			{
				curlevel = 3;
			}//end else if statement
			else if(e.getSource()==level4)
			{
				curlevel = 4;	
			}//end else if statement
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
	}//end RadioListener class
}//end AddPanel class
