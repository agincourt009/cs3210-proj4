import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
	
public class ViewPanel extends JPanel
{
	private static final long serialVersionUID = 1L;
	private JButton logout;
	private JLabel instructions;
	private JList photos;
	private JScrollPane scroll;
	private ArrayList<Object> data;
	private BufferedImage preview;
	private JLabel pictureframe;
	private MainPanel panel;
	 
	public ViewPanel()
	{	
		instructions = new JLabel("Click on the name of the photo you would like to view\nand it will show up on the right.");
		
		logout = new JButton("Logout");
		
		setPreferredSize(new Dimension(400,400));
		
		pictureframe = new JLabel();
		
		/**Can initialize data here, fill it up with values, and then the next line become
		 *photos = new JList(data);
		 */
		photos = new JList();
		/**Add photos accessible with the current access level here*/
		photos.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		photos.setLayoutOrientation(JList.HORIZONTAL_WRAP);
		photos.setVisibleRowCount(10);
		
		ListListener listlisten = new ListListener();
		photos.addListSelectionListener(listlisten);
		
		scroll = new JScrollPane(photos);
		scroll.setPreferredSize(new Dimension(250, 80));
		
		LogoutListener log = new LogoutListener();
		logout.addActionListener(log);
		
		add(instructions);
		add(scroll);
		add(pictureframe);
		add(logout);
	}//end ViewPanel constructor
	
	public void setPanel(MainPanel panel)
	{
		this.panel = panel;
	}//end setPanel method
	
	private class ListListener implements ListSelectionListener
	{
		public void valueChanged(ListSelectionEvent e) 
		{
		    if (e.getValueIsAdjusting() == false) 
		    {
		    	int sel = photos.getSelectedIndex();
		    	/**try 
				*{
				*/
					/**Make this an actual path*/
					/**preview = ImageIO.read(new File(data.get(sel).getPath()));
				*} 
				catch (IOException ex) 
				{
					ex.printStackTrace();
				}
				*/
				pictureframe = new JLabel(new ImageIcon( preview ));
		    }
		}
	}//end ButtonListener class
	
	private class LogoutListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
				panel.logout();
		}//end ActionPerformed method
	}//end ButtonListener class
}//end ViewPanel class