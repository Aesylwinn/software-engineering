/* Implemented by Anthony and Kyle. */
create table User_basic(		-- unverified access profile
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	userType ENUM('BASIC','PROFILE','HOST') NOT NULL,
	username CHAR(20) NOT NULL UNIQUE,
	password CHAR(90) NOT NULL,
	verified BOOLEAN NOT NULL
);

create table User_Profile(		-- std profile
	id_user INT NOT NULL UNIQUE,
	firstName VARCHAR(40) NOT NULL,
	lastName VARCHAR(40) NOT NULL,
	birtday DATE NOT NULL,
	email VARCHAR(40),
	gender ENUM('MALE','FEMALE','OTHER'),
	otherGender VARCHAR(40),
	orientation VARCHAR(3),		-- space for 3 char flags, m,f,o. used to say interest in male, female, and or other
	bio TEXT

);

create table User_Host(			-- business/host profile
	id_user INT NOT NULL UNIQUE,
	displayName VARCHAR(80) NOT NULL UNIQUE,
	businessName VARCHAR(40) NOT NULL,
	bio TEXT
);

create table Event(				-- previously titled interest, changed for clarity
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	id_host INT NOT NULL,
	standardOperation BOOLEAN NOT NULL,	-- if true, this event represents the business' normal hours and procedure
	recurring BOOLEAN NOT NULL,
	displayName VARCHAR(20) NOT NULL,
	id_category INT NOT NULL,
	id_venue INT NOT NULL,
	dateStart DATE NOT NULL,
	dateEnd DATE,-- ---------------used for long events, otherwise ignored
	timeStart TIME NOT NULL,
	timeEnd TIME NOT NULL,
	recurringType ENUM('DAILY','WEEKLY','MONTHLY','FIRST','SECOND','THIRD','FOURTH','LAST'), 	--first,last etc used for first friday, last tuesday, etc
	recurringDay INT,	   /*	changes based on recurType:
							*		daily, first-last: 1-7 to signify day of week (starting sunday as 1), 0 unused
							*		monthly day 1-(29/30/31) to signify day of month
							*/
	description TEXT
);

create table Event_Exceptions(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	id_event INT NOT NULL,
	dateException DATE NOT NULL,
	description TEXT
);

create table Category(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	displayName VARCHAR(20)
);

create table Subcategory(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	id_category INT NOT NULL,
	displayName VARCHAR(20)
);

create table Venue(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	displayName VARCHAR(40) NOT NULL,
	address VARCHAR(40) NOT NULL,
	phoneNumber VARCHAR(20) NOT NULL,
	entryFee DOUBLE NOT NULL,
	description TEXT
);

create table Join_Date(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	id_event INT NOT NULL,
	id_userA INT NOT NULL,
	id_userB INT NOT NULL,
	confirmedA boolean NOT NULL,
	confirmedB boolean NOT NULL
);

create table Join_Event(
	id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
	id_user INT NOT NULL,
	id_event INT NOT NULL,
	rsvp BOOLEAN
);
