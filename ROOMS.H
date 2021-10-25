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

const char* introtext1 = "\
It is the year 2089. \n\
\n\
Mankind has developed a reliance on satellite technology.\n\
\n\
An unexpected pulse from an unidentified stellar phenomenon \n\
strikes the satellite network.\n\
\n\
A chain reaction causes one explosion, then another. \n\
The gigantic satellite network which serves as Earth's \n\
\"artificial ring\" becomes burning wreckage.\n\
\n\
What isn't destroyed by falling steel is destroyed by\n\
opportunistic bandits. \n";
//-
const char* introtext2 = "\
You are Kara.\n\
\n\
You are a twin sister. You and Sara have survived by relying\n\
on each other and salvaging everything you can. \n\
\n\
But she is diabetic, and you are out of insulin. She doesn't have long.\n\
\n\
Kara: \"Don't worry. I'll find your medicine and be back before you know it.\"\n\
\n\
You step out of the door to your makeshift home and lock it behind you.\n\
Better get a move on. \n";

const char* instr = \
"INSTRUCTIONS:\n"\
"You have 15 turns to complete the game.\n\n"\
"Your objective is to find the "\
"medicine that your sister needs and return it to her before the turns reach "\
"zero. Sometimes, you can find food to increase the number of turns left. "\
"You can move between areas in the given direction, and search.\n\n"\
"Press ESCAPE at any time to quit.\n\nGood luck!";

//
const char* room_searched = "You've already thoroughly searched this area.";

//
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
"This old restaurant reeks of mold and refuse. The smell eminating from the \n"\
"kitchen area is nearly vomit-inducing.";
const char* room5_search = \
"Covering your mouth with your arm, you force yourself to poke through the\n"\
"disgusting green goo that fills the pots in the kitchen. Shockingly, you\n"
"find some dried goods that look edible.\n"\
"[You found food. Turns + 3]";

const char* room6_name = "Main Drag - North [6]";
const char* room6_desc = \
"This is the north part of main street. The pavement is cracked and broken\n"\
"here, making progress slow.";
const char* room6_search = \
"You spend the better part of an hour searching through all of the abandoned\n"\
"cars on the street. Unfortunately you found nothing.";

const char* room7_name = "Pet Store [7]";
const char* room7_desc = \
"Old blood stains the empty cages. The pet food shelves have already been\n"\
"searched and anything edible has been taken.";
const char* room7_search = \
"You find one small can of cat food tucked away beneath the shelves.\n"\
"The other people who searched this building must have kicked it underneath.\n"\
"[You found food. Turns + 3]";

const char* room8_name = "Main Drag [8]";
const char* room8_desc = \
"You are in the center of town, on main street. The broken road stretches\n"\
"beyond sight into the smog.";
const char* room8_search = \
"You poke around for a while but can find nothing.";

const char* room9_name = "Garbage Alley [9]";
const char* room9_desc = \
"Bins here are overflowing with nasty-smelling refuse.";
const char* room9_search = \
"All you find is the urge to regurgitate your breakfast.";

const char* room10_name = "Main Drag - East [10]";
const char* room10_desc = \
"The main street turns east here and stretches on out of sight.";
const char* room10_search = \
"Surprisingly, a small rodent scurries away as you overturn a cardboard\n"\
"box. Maybe not all life is gone from the city, after all.";

const char* room11_name = "Power Plant [11]";
const char* room11_desc = \
"To your shock, you detect a faint hum and vibration in the air. The power\n"\
"plant is active - but you certainly haven't seen any evidence of electricty\n"\
"thus far. Whoever is using the power plant is probably trying to keep it\n"\
"a secret...";
const char* room11_search = \
"In the basement you find the master breaker.\n"\
"You flip it off. Whoever is uing the power doesn't have it now.\n"
"[The power grid has been disabled.]";

const char* room11_desc2 = \
"The power plant is dark.";

const char* room12_name = "Main Drag - South [12]";
const char* room12_desc = \
"The southern part of main street has seen more ravage than the rest of\n"\
"the area. There must have been a lot of scuffles around here.";
const char* room12_search = \
"You can't find anything save some expended bullet shells and empty food\n"\
"canisters.";

const char* room13_name = "Dirt Road [13]";
const char* room13_desc = \
"This unpaved stretch connects the rural portion of town with the city.\n";
const char* room13_search = \
"You dig around the surrounding area for a bit but find nothing.";

const char* room14_name = "Old House [14]";
const char* room14_desc = \
"After walking some distance, you arrive at a cul-de-sac of an abandonded\n"\
"neighborhood. Most of the houses have had the doors ripped off or are\n"\
"stained with graffiti. One retains its integrity, however, and you find\n"\
"yourself inside to catch a breath.";
const char* room14_search = \
"The remnants that you find at the bottom of a box of stale cereal do\n"\
"a little to quiet your stomach.\n"\
"[You found food. Turns + 3]";

const char* room15_name = "Bandit Headquarters [15]";
const char* room15_desc = \
"There are bandits everywhere here. You are safe where you are, but it's\n"\
"too dangerous to proceed right now. You think you can see flickering lights\n"\
"inside...";
const char* room15_search = \
"Oh, no! The bandits catch you as you are rummaging around.\n"\
"Thankfully, they make your end quick...\n\n\nGAME      OVER";
const char* room15_desc2 = \
"The bandits must have been using power from the plant. They are running\n"\
"around in a panic, trying to figure out what happened. Now is your chance\n"\
"to sneak inside.";

const char* room16_name = "Bandit HQ - Cold Storage [16]";
const char* room16_desc = \
"The bandits must have been stashing goods here for ages. There's all kinds\n"\
"of medicines. Surely you can find something for Kara here.";
const char* room16_search = \
"You very quickly find packs of insulin that Kara can use. Thank goodness - \n"\
"time to get back to her before it's too late.\n"\
"[You found the medicine.]";


// Proper test 
const char* roomNames[17] = { \
    0, room1_name, room2_name, room3_name, room4_name, 
    room5_name, room6_name, room7_name, room8_name, 
    room9_name, room10_name, room11_name, room12_name,
    room13_name, room14_name, room15_name, room16_name
};
const char* roomDescriptions[17] = { \
    0, room1_desc, room2_desc, room3_desc, room4_desc, 
    room5_desc, room6_desc, room7_desc, room8_desc, 
    room9_desc, room10_desc, room11_desc, room12_desc, 
    room13_desc, room14_desc, room15_desc, room16_desc 
};
const char* roomSearches[17] = { \
    0, room1_search, room2_search, room3_search, room4_search, 
    room5_search, room6_search, room7_search, room8_search, 
    room9_search, room10_search, room11_search, room12_search, 
    room13_search, room14_search, room15_search, room16_search
};

ROOM rooms[17];