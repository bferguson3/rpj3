// Map

typedef struct _room {
    const char** roomName;
    const char** entryDesc;
    const char** searchDesc;
	void* exit_N;
    void* exit_E;
    void* exit_S;
    void* exit_W;
} ROOM;

// Initial test

/*
It is the year 2089. 

Mankind has developed a reliance on satellite technology.

An unexpected pulse from an unidentified stellar phenomenon 
strikes the satellite network.

A chain reaction causes one explosion, then another. 
The gigantic satellite network which serves as Earth's 
"artificial ring" becomes burning wreckage.

What isn't destroyed by falling steel is destroyed by
opportunistic bandits. 

-

You are Kara.

You are a twin sister. You and Sara have survived by relying
on each other and salvaging everything you can. 

But she is diabetic, and you are out of insulin. She doesn't have long.

Kara: "Don't worry. I'll find your medicine and be back before you know it."

You step out of the door to your makeshift home and lock it behind you.
Better get a move on. 
*/

const char* room_searched = "You've already thoroughly searched this area."

const char* room1_name = "Ruined Office Building [1]";
const char* room1_desc = \
"A sticky grey layer of dust covers everything. Cobwebs hang from filing\n"\
"cabinets stretched to the tiled ceiling. If you are lucky, you are the\n"\
"only one here.";
const char* room1_search = \
"You take a moment and look around.\n"\
"You and Sara have already stripped this place of all useful supplies.";

const char* room2_name = "Office Building - Alley [2]";
const char* room2_desc = \
"A chill wind blows through the alley in between the office building\n"\
"main and the nearby annex. A howl is heard in the distance, but you aren\'t\n"\
"sure if it's some animal or just the wind...";
const char* room2_search = \
"You poke through the refuse piles in the alley corners.\n"\
"You can\'t find anything useful.";

const char* room3_name = "Office Building - Annex [3]";
const char* room3_desc = \
"This secondary office building has been completely stripped to the under-\n"\
"lying structure. It doesn't look like anyone has been in here for a while.";
const char* room3_search = \
"You check every corner of every room, but turn up nothing. Just as you\n"\
"turn to leave, you spy one last candy bar left in a vending machine.\n"
"[You found food. Turns + 3]";

const char* room4_name = "Plaza Side Road [4]";
const char* room4_desc = \
"This road leads away from the office plaza and main drag. The sun beats\n"
"down hard here, tinging everything yellow through the smog.";
const char* room4_search = \
"Nothing can be found around the road here besides rocks and weeds.";

const char* room5_name = "Run-down Chick'n Shack [5]";
const char* room5_desc = \
"";
const char* room5_search = \
"";

ROOM room1, room2, room3, room4, room5, room6, room7, room8, \
    room9, room10, room11, room12, room13, room14, room15, room16;

// Proper test 
const char* roomNames[17] = { \
    0, room1_name, room2_name, room3_name, room4_name, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const char* roomDescriptions[17] = { \
    0, room1_desc, room2_desc, room3_desc, room4_desc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const char* roomSearches[17] = { \
    0, room1_search, room2_search, room3_search, room4_search, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
ROOM rooms[17];