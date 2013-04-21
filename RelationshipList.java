import java.util.ArrayList;
public class RelationshipList implements java.io.Serializable 
{
	private static final long serialVersionUID = 1L;
	private ArrayList<User> users;
	private ArrayList<ArrayList<User>> friends, family;
	
	public RelationshipList() 
	{
		users = new ArrayList<User>();
		friends = new ArrayList<ArrayList<User>>();
		family = new ArrayList<ArrayList<User>>();
	}//end RelationshipList constructor
	
	public void addUser(User user)
	{
		users.add(user);
		ArrayList<User> friend = new ArrayList<User>();
		ArrayList<User> famil = new ArrayList<User>();
		friends.add(friend);
		family.add(famil);
	}//end addUser method
	
	public void addFriend(User user, User friend)
	{
		int index = users.indexOf(user);
		friends.get(index).add(friend);
	}//end addFriend method
	
	public void addFamily(User user, User famil)
	{
		int index = users.indexOf(user);
		family.get(index).add(famil);
	}//end addFamily method
	
	public ArrayList<User> getFriends(User user)
	{
		int index = users.indexOf(user);
		return friends.get(index);
	}//end friends getter;
	
	public ArrayList<User> getFamily(User user)
	{
		int index = users.indexOf(user);
		return family.get(index);
	}//end friends getter;
	
	public boolean isFriend(User user, User friend)
	{
		int index = users.indexOf(user);
		if(friends.get(index).contains(friend))
		{
			return true;
		}//end if statement
		return false;
	}//end isFriend method
	
	public boolean isFamily(User user, User famil)
	{
		int index = users.indexOf(user);
		if(family.get(index).contains(famil))
		{
			return true;
		}//end if statement
		return false;
	}//end isFriend method
}//end RelationshipList class
