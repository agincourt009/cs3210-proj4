import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import com.sun.jna.Library;
import com.sun.jna.Native;

public class MainPanel extends JFrame
{
	private ViewPanel view;
	private LoginPanel login;
	private AddPanel add;
	private UserPanel user;
	private FirstPanel first;
	private int curlevel;
	public MainPanel(ViewPanel view, LoginPanel login, AddPanel add, UserPanel user, FirstPanel first)
	{
		this.view = view;
		this.login = login;
		this.add = add;
		this.user = user;
		this.first = first;
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
	
	public interface CStdLib extends Library 
	{
        int syscall(int number, Object... args);
    }//end CStdLib interface
	
	public static void main(String[] args)
	{
		ViewPanel view = new ViewPanel();
		LoginPanel login = new LoginPanel();
		FirstPanel first = new FirstPanel();
		AddPanel add = new AddPanel();
		UserPanel user = new UserPanel();
		
		MainPanel panel = new MainPanel(view, login, add, user, first);
		
		panel.setPreferredSize(new Dimension(500,500));
		
		panel.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		view.setPanel(panel);
		login.setPanel(panel);
		first.setPanel(panel);
		add.setPanel(panel);
		user.setPanel(panel);
		
		CStdLib c = (CStdLib)Native.loadLibrary("c", CStdLib.class);
		int ret = c.syscall(290, "/tmp/create-new-directory-here");
		if(ret == 1)
		{
			panel.getContentPane().add(first);
		}//end if statement
		else
		{
			panel.getContentPane().add(login);
		}//end else statement
		
		panel.pack();
		panel.setVisible(true);
	}//end main method
}//end MainPanel class
