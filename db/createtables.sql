/* Implemented by Kyle and Anthony. */
create table User_basic(
	id LONG,
	username CHAR(20),
	password CHAR(20),
	verified BOOLEAN
);

create table User_Profile(
	id_user LONG,
	firstName VARCHAR(20),
	lastName VARCHAR(20)
	
);

create table User_Profesional(
	id_user LONG,
	displayName VARCHAR(40),
	businessName VARCHAR(40)
);

create table Interest_Single(
	displayName VARCHAR(20),
	id_category LONG,
	description TEXT
	
);

create table Interest_Recurring(
	displayName VARCHAR(20),
	id_category LONG,
	description TEXT
);

create table Category(
	id LONG,
	displayName VARCHAR(20)
	
);

create table Venue(
	id_venue LONG,
	address VARCHAR(40),
	phoneNumber VARCHAR(20)
);

create table Join_Date(
	userA VARCHAR(20),
	confirmedA boolean,
	userB VARCHAR(20),
	confirmedB boolean
);
