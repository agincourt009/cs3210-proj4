import javax.swing.*;
import java.awt.*;
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
	private String curUser;
	
	public MainPanel(ViewPanel view, LoginPanel login, AddPanel add, UserPanel user, NewPanel newp, RelationshipPanel relation)
	{
		this.view = view;
		this.login = login;
		this.add = add;
		this.user = user;
		this.newp = newp;
		this.relation = relation;
	}//end MainPanel constructor
	public void logout()
	{
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
	
	public void switchView()
	{
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
	
	public void setCurUser(String user)
	{
		this.curUser = user;
	}//end curUser setter
	
	public String getCurUser()
	{
		return curUser;
	}//end curUser getter
	
	public static void main(String[] args)
	{
		ViewPanel view = new ViewPanel();
		LoginPanel login = new LoginPanel();
		AddPanel add = new AddPanel();
		UserPanel user = new UserPanel();
		NewPanel newp = new NewPanel();
		RelationshipPanel relation = new RelationshipPanel();
		
		MainPanel panel = new MainPanel(view, login, add, user, newp, relation);
		
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
}//end MainPanel class
