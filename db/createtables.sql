/* Implemented by Kyle and Anthony. */
create table User_basic(		--unverified access profile
	id LONG,
	userType ENUM('BASIC','PROFILE','HOST'),
	username CHAR(20) PRIMARY KEY,
	password CHAR(20),
	verified BOOLEAN
);

create table User_Profile(		--std profile, created after account verification
	id_user LONG,
	firstName VARCHAR(40),
	lastName VARCHAR(40),
	gender ENUM('MALE','FEMALE','OTHER'),
	otherGender VARCHAR(40),
	orientation VARCHAR(3),		--space for 3 char flags, m,f,o. used to say interest in male, female, and or other
	bio TEXT
	
);

create table User_Host(			--business/host profile
	id_user LONG,
	displayName VARCHAR(80),
	businessName VARCHAR(40)
);

create table Event_Single(		--previously titled interest, changed for clarity
	id LONG,					--used for single day, one-off events
	displayName VARCHAR(20),	
	id_category LONG,
	id_venue LONG,
	dateStart DATE,
	timeStart TIME,
	timeEnd TIME,
	description TEXT
);

create table Event_Recurring(	
	id LONG,
	displayName VARCHAR(20),
	id_category LONG,
	id_venue LONG,
	recurringType ENUM('DAILY','WEEKLY','MONTHLY','FIRST','SECOND','THIRD','LAST'), 	--first,last etc used for first friday, last tuesday, etc
	recurringDay INT,		--effect changes based on recurType: 
	recurringTime TIME,		--^--daily, first-last: 1-7 to signify day of week (starting monday)
	description TEXT		--^--monthly day 1-(29/30/31) valid to determine day of month
);

create table Event_Long(		--for several day events like a fair or music festival
	id LONG,					
	displayName VARCHAR(20),	
	id_category LONG,
	id_venue LONG,
	dateStart DATE,
	dateEnd	DATE,
	timeStart TIME,
	timeEnd TIME,
	description TEXT
);

create table Category(
	id LONG,
	id_
	displayName VARCHAR(20)
	
);

create table Venue(
	id LONG,
	address VARCHAR(40),
	phoneNumber VARCHAR(20)
	entryFee DOUBLE,
);

create table Join_Date(
	id LONG,
	id_venue LONG,
	id_userA LONG,
	id_userB LONG,
	confirmedA boolean,
	confirmedB boolean
);
