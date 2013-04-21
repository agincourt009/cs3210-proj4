
public class User implements java.io.Serializable
{
	private static final long serialVersionUID = 1L;
	private String user;
	public User(String user)
	{
		this.user = user;
	}//end user constructor
	
	public void setUser(String user)
	{
		this.user = user;
	}//end user setter
	
	public String getUser()
	{
		return user;
	}//end user getter
}//end user class
