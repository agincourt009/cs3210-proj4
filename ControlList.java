import java.util.ArrayList;
import javax.swing.*;

public class ControlList implements java.io.Serializable
{
	private static final long serialVersionUID = 1L;
	private ArrayList<String> files;
	private ArrayList<Boolean> friends, family, everyone;
	private ArrayList<User>users;
	private RelationshipList relation;
	private JPanel panel;
	
	public ControlList()
	{
		files = new ArrayList<String>();
		friends = new ArrayList<Boolean>();
		family = new ArrayList<Boolean>();
		users = new ArrayList<User>();
		everyone = new ArrayList<Boolean>();
		panel = new JPanel();
	}//end ControlList constructor
	
	public void addFile(String filename, User user, boolean friends, boolean family, boolean everyone)
	{
		files.add(filename);
		String output = new String();
		for(int i = 0; i<files.size();i++)
		{
			output = output + files.get(i) + "\n";
		}//end for loop
		Boolean every = new Boolean(everyone);
		Boolean friend = new Boolean(friends);
		Boolean fam = new Boolean(family);
		this.users.add(user);
		this.everyone.add(every);
		this.friends.add(friend);
		this.family.add(fam);
		
		JOptionPane.showMessageDialog(panel,"Current files:" + output+ "\nEveryone: " + every.booleanValue() + "\nFriends: " + friend.booleanValue() + "\nFamily: " + fam.booleanValue());
		
	}//end file adder
	
	public boolean hasAccess(String filePath, User user)
	{
		int index = files.indexOf(filePath);
		if(user==users.get(index))
		{
			return true;
		}//end if statement
		else if(friends.get(index).booleanValue())
		{
			if(relation.isFriend(users.get(index), user))
			{
				return true;
			}//end if statement
		}//end else statement
		else if(family.get(index).booleanValue())
		{
			if(relation.isFamily(users.get(index), user))
			{
				return true;
			}//end if statement
		}//end else if statement
		return false;
	}//end hasAccess class
	
	public boolean isEveryone(String fileName)
	{
		int index = files.indexOf(fileName);
		return everyone.get(index).booleanValue();
	}//end isEveryone method
	
	public ArrayList<String> getFiles(User user)
	{
		ArrayList<String> data = new ArrayList<String>();
		
		for(int i = 0;i<files.size();i++)
		{
			if(everyone.get(i).booleanValue())
			{
				data.add(files.get(i));
			}//end if statement
			else if(friends.get(i).booleanValue()&&relation.isFriend(users.get(i), user))
			{
				data.add(files.get(i));
			}//end else if statement
			else if(family.get(i).booleanValue()&&relation.isFamily(users.get(i), user))
			{
				data.add(files.get(i));
			}//end else if
			else if(user.getUser().equals(users.get(i).getUser()))
			{
				data.add(files.get(i));
			}//end else if
		}//end for loop
		return data;
	}//end getFiles method
}//end ControlList class
