import java.util.ArrayList;

public class ControlList implements java.io.Serializable
{
	private static final long serialVersionUID = 1L;
	private ArrayList<String> files, names, users;
	private ArrayList<Boolean> friends, family, everyone;
	
	public ControlList()
	{
		files = new ArrayList<String>();
		friends = new ArrayList<Boolean>();
		family = new ArrayList<Boolean>();
		users = new ArrayList<String>();
		everyone = new ArrayList<Boolean>();
		names = new ArrayList<String>();
	}//end ControlList constructor
	
	public void addFile(String filename, String user, boolean friends, boolean family, boolean everyone, MainPanel panel, String fileName)
	{
		files.add(filename);
		names.add(fileName); 
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
		
	}//end file adder
	
	public boolean hasAccess(String filePath, String user, RelationshipList relation)
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
	
	public ArrayList<String> getFiles(String user, RelationshipList relation)
	{
		ArrayList<String> data = new ArrayList<String>();
		
		for(int i = 0;i<names.size();i++)
		{
			if(everyone.get(i).booleanValue())
			{
				data.add(names.get(i));
			}//end if statement
			else if(friends.get(i).booleanValue()&&relation.isFriend(users.get(i), user))
			{
				data.add(names.get(i));
			}//end else if statement
			else if(family.get(i).booleanValue()&&relation.isFamily(users.get(i), user))
			{
				data.add(names.get(i));
			}//end else if
			else if(user.equals(users.get(i)))
			{
				data.add(names.get(i));
			}//end else if
		}//end for loop
		return data;
	}//end getFiles method
	
	public String getPath(String name)
	{
		int index = names.indexOf(name);
		return files.get(index);
	}
}//end ControlList class
