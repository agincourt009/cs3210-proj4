import java.util.ArrayList;
public class RelationshipList implements java.io.Serializable 
{
	private static final long serialVersionUID = 1L;
	private ArrayList<String> users;
	private ArrayList<ArrayList<String>> friends, family;
	
	public RelationshipList() 
	{
		users = new ArrayList<String>();
		friends = new ArrayList<ArrayList<String>>();
		family = new ArrayList<ArrayList<String>>();
	}//end RelationshipList constructor
	
	public void addUser(String user)
	{
		users.add(user);
		ArrayList<String> friend = new ArrayList<String>();
		ArrayList<String> famil = new ArrayList<String>();
		friends.add(friend);
		family.add(famil);
	}//end addUser method
	
	public void addFriend(String user, String friend)
	{
		int index = users.indexOf(user);
		friends.get(index).add(friend);
		int in = users.indexOf(friend);
		friends.get(in).add(user);
	}//end addFriend method
	
	public void addFamily(String user, String famil)
	{
		int index = users.indexOf(user);
		family.get(index).add(famil);
		int in = users.indexOf(famil);
		family.get(in).add(user);
	}//end addFamily method
	
	public ArrayList<String> getFriends(String user)
	{
		int index = users.indexOf(user);
		return friends.get(index);
	}//end friends getter;
	
	public ArrayList<String> getFamily(String user)
	{
		int index = users.indexOf(user);
		return family.get(index);
	}//end friends getter;
	
	public boolean isFriend(String user, String friend)
	{
		int index = users.indexOf(user);
		boolean ret = false;
		for(int i = 0; i<friends.get(index).size(); i++)
		{
			if(friends.get(index).get(i).equals(friend))
			{
				return true;
			}//end if statement
		}//end for loop
		if(friends.get(index).contains(friend))
		{
			return true;
		}//end if statement
		return ret;
	}//end isFriend method
	
	public boolean isFamily(String user, String famil)
	{
		int index = users.indexOf(user);
		boolean ret = false;
		for(int i = 0; i<family.get(index).size(); i++)
		{
			if(family.get(index).get(i).equals(famil))
			{
				return true;
			}//end if statement
		}//end for loop
		if(family.get(index).contains(famil))
		{
			return true;
		}//end if statement
		return ret;
	}//end isFriend method
}//end RelationshipList class
