public final class Person implements Cloneable
{
	private Name name;
	private String ssn;
	private int age;

	public Person (String ssn, int age, Name name)
	{
		this.name = name;
		this.ssn = ssn;
		this.age = age;
	}
	
	// Getter & Setter Methods
	// ssn
	public void setSsn (String ssn)
	{
		this.ssn = ssn;
	}
	public String getSsn()
	{
		return this.ssn;
	}
	// age
	public void setAge(int age)
	{
		this.age = age;
	}
	public int getAge()
	{
		return this.age;
	}
	// name
	public void setName(Name name)
	{
		this.name = name;
	}
	public Name getName()
	{
		return this.name;
	}
	@Override public String toString()
	{
		return this.name + " " + this.ssn + " " + " " + this.age;
	
	}
	@Override public Person clone() 
	{
		try {
			/* Test 6 (Deep copy) :
			   Person personClone = (Person) super.clone();
		}
	}
}
