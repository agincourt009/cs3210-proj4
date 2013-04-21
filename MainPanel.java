import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class MainPanel extends JFrame
{
	private static final long serialVersionUID = 1L;
	private ViewPanel view;
	private LoginPanel login;
	private AddPanel add;
	private UserPanel user;
	private NewPanel newp;
	private RelationshipPanel relation;
	private int curlevel;
	private User curUser;
	private RelationshipList relations;
	private ControlList control;
	
	public static void main(String[] args)
	{
		ViewPanel view = new ViewPanel();
		LoginPanel login = new LoginPanel();
		AddPanel add = new AddPanel();
		UserPanel user = new UserPanel();
		NewPanel newp = new NewPanel();
		RelationshipPanel relation = new RelationshipPanel();
		RelationshipList relations = new RelationshipList();
		ControlList control = new ControlList();
		
		MainPanel panel = new MainPanel(view, login, add, user, newp, relation, relations, control);
		
		try
	    {
	         FileInputStream fileIn = new FileInputStream("relations.ser");
	         ObjectInputStream in = new ObjectInputStream(fileIn);
	         relations = (RelationshipList) in.readObject();
	         in.close();
	         fileIn.close();
	         
	         fileIn = new FileInputStream("control.ser");
	         in = new ObjectInputStream(fileIn);
	         control = (ControlList) in.readObject();
	         in.close();
	         fileIn.close();
	    }//end try block
		catch(IOException i)
	    {
	         i.printStackTrace();
	         return;
	    }//end catch block
		catch(ClassNotFoundException c)
	    {
	         System.out.println("RelationshipList or ControlList class not found.");
	         c.printStackTrace();
	         return;
	    }//end catch block
		
		panel.setPreferredSize(new Dimension(500,500));
		
		panel.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		view.setPanel(panel);
		login.setPanel(panel);
		add.setPanel(panel);
		user.setPanel(panel);
		newp.setPanel(panel);
		relation.setPanel(panel);
		
		panel.getContentPane().add(login);
		
		panel.pack();
		panel.setVisible(true);
	}//end main method

	public MainPanel(ViewPanel view, LoginPanel login, AddPanel add, UserPanel user, NewPanel newp, RelationshipPanel relation, RelationshipList relations, ControlList control)
	{
		this.view = view;
		this.login = login;
		this.add = add;
		this.user = user;
		this.newp = newp;
		this.relation = relation;
		this.relations = relations;
		this.control = control;
		curlevel = 0;		

		CloseHandler close = new CloseHandler();
		addWindowListener(close);
		setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);

	}//end MainPanel constructor
	public void logout()
	{
		curlevel = 0;
		curUser = null;
		this.getContentPane().removeAll();
		this.getContentPane().add(login);
	}//end logout method
	
	public void switchAdd()
	{
		this.getContentPane().removeAll();
		this.getContentPane().add(add);
	}//end switchAdd method
	
	public void switchUser()
	{
		this.getContentPane().removeAll();
		this.getContentPane().add(user);
	}//en switchUser method
	
	public void switchView(boolean login)
	{
		view.setLogin(login);
		this.getContentPane().removeAll();
		this.getContentPane().add(view);
	}//end switchView method
	
	public void switchNew()
	{
		this.getContentPane().removeAll();
		this.getContentPane().add(newp);
	}//end switchNew method
	
	public void switchRelationship()
	{
		this.getContentPane().removeAll();
		this.getContentPane().add(relation);
	}//end switchNew method
	
	public void addData()
	{
		
	}//end addData method
	
	public ArrayList<Object> getData()
	{
		ArrayList<Object> data = new ArrayList<Object>();
		return data;
	}//end getData method
	
	public void setCurlevel(int curlevel)
	{
		this.curlevel = curlevel;
	}//end curlevel setter
	
	public int getCurlevel()
	{
		return curlevel;
	}//end curlevel getter
	
	public void setCurUser(User user)
	{
		this.curUser = user;
	}//end curUser setter
	
	public User getCurUser()
	{
		return curUser;
	}//end curUser getter
	
	public void setRelations(RelationshipList relations)
	{
		this.relations = relations;
	}//end relations setter
	
	public RelationshipList getRelations()
	{
		return relations;
	}//end relations getter
	
	public void setControl(ControlList control)
	{
		this.control = control;
	}//end control setter
	
	public ControlList getControl()
	{
		return control;
	}//end control getter
	
	public void saveControl()
	{
		try
	    {
	         FileOutputStream fileOut = new FileOutputStream("control.ser");
	         ObjectOutputStream out = new ObjectOutputStream(fileOut);
	         out.writeObject(control);
	         out.close();
	         fileOut.close();
	    }//end try block
		catch(IOException i)
	    {
	          i.printStackTrace();
	    }//end catch block
	}//end saveControl method
	
	public void saveRelations()
	{
		try
		{
		     FileOutputStream fileOut = new FileOutputStream("relations.ser");
		     ObjectOutputStream out = new ObjectOutputStream(fileOut);
		     out.writeObject(relations);
		     out.close();
		     fileOut.close();
		}//end try block
		catch(IOException i)
		{
		     i.printStackTrace();
		}//end catch block
	}//end saveRelations method
	
	private class CloseHandler extends WindowAdapter 
	{
		  public void windowClosing(WindowEvent evt) 
		  {
			  saveControl();
			  saveRelations();
			  System.exit(0);
		  }
	}//end CloseHandler class
}//end MainPanel class
