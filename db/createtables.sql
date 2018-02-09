/* Implemented by Kyle and Anthony. */
create table User(
	username VARCHAR(20),
	password VARCHAR(20),
	verified BOOLEAN
);

create table Interest(
	name VARCHAR(20),
	category VARCHAR(20),
	description VARCHAR(128),
);

create table Venue(
	address VARCHAR(40),
	phoneNumber VARCHAR(20),
);

create table Time(
	startTime VARCHAR(20),
	startTime VARCHAR(20),
);

create table joinDate(
	userA VARCHAR(20),
	confirmedA boolean,
	userB VARCHAR(20),
	confirmedB boolean,
);
