﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GTA
{
    public enum VehicleLock
    {
        Unlocked = 1,
        Locked = 2,
        Unknown_3 = 3,
        LockedInside = 4
    }
    
    public enum TextStyle
    {
        MissionPassed = 1,
        MissionName = 2,
        Restart = 3,
        Message1 = 4,
        Message2 = 5,
        CenterMessage = 6,
        CenterHeading = 7
    }

    public enum FrontendSound
    {
        //Explosion = 0x2B,
        Garage1 = 0xE,
        Garage2 = 0xF,
        Garage3 = 0x10,
        Garage4 = 0x11,
        WeaponPickup = 0x6,
        CollectiblePickup = 0xD,
        AdrenalinePickup = 0x9,
        ArmorPickup = 0xA,
        HealthPickup = 0x8,
        Pickup = 0xB,
        MoneyPickup = 0xD,
        WeaponPickupB = 0x7,
        USJPassed = 0x2B,
        Menu1 = 0x23,
        TimerEnd = 0x21
    }

    public enum PedID
    {
        @null = 0,
		male01 = 7,
		BFORI = 9,
		BFOST = 10,
		VBFYCRP = 11,
		BFYRI = 12,
		BFYST = 13,
		BMORI = 14,
		BMOST = 15,
		BMYAP = 16,
		BMYBU = 17,
		BMYBE = 18,
		BMYDJ = 19,
		BMYRI = 20,
		BMYCR = 21,
		BMYST = 22,
		WMYBMX = 23,
		WBDYG1 = 24,
		WBDYG2 = 25,
		WMYBP = 26,
		WMYCON = 27,
		BMYDRUG = 28,
		WMYDRUG = 29,
		HMYDRUG = 30,
		DWFOLC = 31,
		DWMOLC1 = 32,
		DWMOLC2 = 33,
		DWMYLC1 = 34,
		HMOGAR = 35,
		WMYGOL1 = 36,
		WMYGOL2 = 37,
		HFORI = 38,
		HFOST = 39,
		HFYRI = 40,
		HFYST = 41,
		HMORI = 43,
		HMOST = 44,
		HMYBE = 45,
		HMYRI = 46,
		HMYCR = 47,
		HMYST = 48,
		OMOKUNG = 49,
		WMYMECH = 50,
		BMYMOUN = 51,
		WMYMOUN = 52,
		OFORI = 53,
		OFOST = 54,
		OFYRI = 55,
		OFYST = 56,
		OMORI = 57,
		OMOST = 58,
		OMYRI = 59,
		OMYST = 60,
		WMYPLT = 61,
		WMOPJ = 62,
		BFYPRO = 63,
		HFYPRO = 64,
		BMYPOL1 = 66,
		BMYPOL2 = 67,
		WMOPREA = 68,
		SBFYST = 69,
		WMOSCI = 70,
		WMYSGRD = 71,
		SWMYHP1 = 72,
		SWMYHP2 = 73,
		SWFOPRO = 75,
		WFYSTEW = 76,
		SWMOTR1 = 77,
		WMOTR1 = 78,
		BMOTR1 = 79,
		VBMYBOX = 80,
		VWMYBOX = 81,
		VHMYELV = 82,
		VBMYELV = 83,
		VIMYELV = 84,
		VWFYPRO = 85,
		VWFYST1 = 87,
		WFORI = 88,
		WFOST = 89,
		WFYJG = 90,
		WFYRI = 91,
		WFYRO = 92,
		WFYST = 93,
		WMORI = 94,
		WMOST = 95,
		WMYJG = 96,
		WMYLG = 97,
		WMYRI = 98,
		WMYRO = 99,
		WMYCR = 100,
		WMYST = 101,
		BALLAS1 = 102,
		BALLAS2 = 103,
		BALLAS3 = 104,
		FAM1 = 105,
		FAM2 = 106,
		FAM3 = 107,
		LSV1 = 108,
		LSV2 = 109,
		LSV3 = 110,
		MAFFA = 111,
		MAFFB = 112,
		MAFBOSS = 113,
		VLA1 = 114,
		VLA2 = 115,
		VLA3 = 116,
		TRIADA = 117,
		TRIADB = 118,
		TRIBOSS = 120,
		DNB1 = 121,
		DNB2 = 122,
		DNB3 = 123,
		VMAFF1 = 124,
		VMAFF2 = 125,
		VMAFF3 = 126,
		VMAFF4 = 127,
		DNMYLC = 128,
		DNFOLC1 = 129,
		DNFOLC2 = 130,
		DNFYLC = 131,
		DNMOLC1 = 132,
		DNMOLC2 = 133,
		SBMOTR2 = 134,
		SWMOTR2 = 135,
		SBMYTR3 = 136,
		SWMOTR3 = 137,
		WFYBE = 138,
		BFYBE = 139,
		HFYBE = 140,
		SOFYBU = 141,
		SBMYST = 142,
		SBMYCR = 143,
		BMYCG = 144,
		WFYCRK = 145,
		HMYCM = 146,
		WMYBU = 147,
		BFYBU = 148,
		WFYBU = 150,
		DWFYLC1 = 151,
		WFYPRO = 152,
		WMYCONB = 153,
		WMYBE = 154,
		WMYPIZZ = 155,
		BMOBAR = 156,
		CWFYHB = 157,
		CWMOFR = 158,
		CWMOHB1 = 159,
		CWMOHB2 = 160,
		CWMYFR = 161,
		CWMYHB1 = 162,
		BMYBOUN = 163,
		WMYBOUN = 164,
		WMOMIB = 165,
		BMYMIB = 166,
		WMYBELL = 167,
		BMOCHIL = 168,
		SOFYRI = 169,
		SOMYST = 170,
		VWMYBJD = 171,
		VWFYCRP = 172,
		SFR1 = 173,
		SFR2 = 174,
		SFR3 = 175,
		BMYBAR = 176,
		WMYBAR = 177,
		WFYSEX = 178,
		WMYAMMO = 179,
		BMYTATT = 180,
		VWMYCR = 181,
		VBMOCD = 182,
		VBMYCR = 183,
		VHMYCR = 184,
		SBMYRI = 185,
		SOMYRI = 186,
		SOMYBU = 187,
		SWMYST = 188,
		WMYVA = 189,
		COPGRL3 = 190,
		GUNGRL3 = 191,
		MECGRL3 = 192,
		NURGRL3 = 193,
		CROGRL3 = 194,
		GANGRL3 = 195,
		CWFOFR = 196,
		CWFOHB = 197,
		CWFYFR1 = 198,
		CWFYFR2 = 199,
		CWMYHB2 = 200,
		DWFYLC2 = 201,
		DWMYLC2 = 202,
		OMYKARA = 203,
		WMYKARA = 204,
		WFYBURG = 205,
		VWMYCD = 206,
		VHFYPRO = 207,
		OMONOOD = 209,
		OMOBOAT = 210,
		WFYCLOT = 211,
		VWMOTR1 = 212,
		VWMOTR2 = 213,
		VWFYWAI = 214,
		SBFORI = 215,
		SWFYRI = 216,
		WMYCLOT = 217,
		SBFOST = 218,
		SBFYRI = 219,
		SBMOCD = 220,
		SBMORI = 221,
		SBMOST = 222,
		SHMYCR = 223,
		SOFORI = 224,
		SOFOST = 225,
		SOFYST = 226,
		SOMOBU = 227,
		SOMORI = 228,
		SOMOST = 229,
		SWMOTR5 = 230,
		SWFORI = 231,
		SWFOST = 232,
		SWFYST = 233,
		SWMOCD = 234,
		SWMORI = 235,
		SWMOST = 236,
		SHFYPRO = 237,
		SBFYPRO = 238,
		SWMOTR4 = 239,
		SWMYRI = 240,
		SMYST = 241,
		SMYST2 = 242,
		SFYPRO = 243,
		VBFYST2 = 244,
		VBFYPRO = 245,
		VHFYST3 = 246,
		BIKERA = 247,
		BIKERB = 248,
		BMYPIMP = 249,
		SWMYCR = 250,
		WFYLG = 251,
		WMYVA2 = 252,
		BMOSEC = 253,
		BIKDRUG = 254,
		WMYCH = 255,
		SBFYSTR = 256,
		SWFYSTR = 257,
		HECK1 = 258,
		HECK2 = 259,
		BMYCON = 260,
		WMYCD1 = 261,
		BMOCD = 262,
		VWFYWA2 = 263,
		WMOICE = 264,
		laemt1 = 274,
		lvemt1 = 275,
		sfemt1 = 276,
		lafd1 = 277,
		lvfd1 = 278,
		sffd1 = 279,
		lapd1 = 280,
		sfpd1 = 281,
		lvpd1 = 282,
		csher = 283,
		lapdm1 = 284,
		swat = 285,
		fbi = 286,
		army = 287,
		dsher = 288,
		special01 = 290,
		special02 = 291,
		special03 = 292,
		special04 = 293,
		special05 = 294,
		special06 = 295,
		special07 = 296,
		special08 = 297,
		special09 = 298,
		special10 = 299
    }

    public enum CarID
    {
        AT400 = 577,
        Admiral = 445,
        Alpha = 602,
        Ambulance = 416,
        Andromada = 592,
        Artict1 = 435,
        Artict2 = 450,
        Artict3 = 591,
        BF400 = 581,
        BFInjection = 424,
        Baggage = 485,
        BaggageTrailerA = 606,
        BaggageTrailerB = 607,
        Bandito = 568,
        Banshee = 429,
        Barracks = 433,
        Beagle = 511,
        Benson = 499,
        Bike = 509,
        BlackBoxville = 609,
        Blade = 536,
        Blista = 496,
        BloodringBanger = 504,
        Bmx = 481,
        Bobcat = 422,
        Boxville = 498,
        Bravura = 401,
        Broadway = 575,
        Buccaneer = 518,
        Buffalo = 402,
        Bullet = 541,
        Burrito = 482,
        Bus = 431,
        Cabbie = 438,
        Caddy = 457,
        Cadrona = 527,
        Camper = 483,
        Cargobob = 548,
        CementTruck = 524,
        Cheetah = 415,
        Clover = 542,
        Club = 589,
        Coach = 437,
        Coastguard = 472,
        CombineHarvester = 532,
        Comet = 480,
        Cropduster = 512,
        DFT30 = 578,
        Dingy = 473,
        Dodo = 593,
        Dozer = 486,
        Dumper = 406,
        Dune = 573,
        Elegant = 507,
        Elegy = 562,
        Emperor = 585,
        Enforcer = 427,
        Esperanto = 419,
        Euros = 587,
        FBIRancher = 490,
        FBITruck = 528,
        FCR900 = 521,
        Faggio = 462,
        FarmTrailer = 610,
        Feltzer = 533,
        FireTruck = 407,
        FireTruckA = 544,
        Flash = 565,
        Flatbed = 455,
        Forklift = 530,
        Fortune = 526,
        Freeway = 463,
        Glendale = 466,
        Glenshit = 604,
        Greenwood = 492,
        HPV1000 = 523,
        Hermes = 474,
        Hotdog = 588,
        Hotknife = 434,
        Hotring = 494,
        HotringA = 502,
        HotringB = 503,
        Hunter = 425,
        Huntley = 579,
        Hustler = 545,
        Hydra = 520,
        Infernus = 411,
        Intruder = 546,
        Jester = 559,
        Jetmax = 493,
        Journey = 508,
        Kart = 571,
        Landstalker = 400,
        Launch = 595,
        Leviathon = 417,
        Linerunner = 403,
        LureRancher = 505,
        Majestic = 517,
        Manana = 410,
        Marquis = 484,
        Maverick = 487,
        Merit = 551,
        Mesa = 500,
        Monster = 444,
        Monstera = 556,
        Monsterb = 557,
        Moonbeam = 418,
        MountainBike = 510,
        Mower = 572,
        MrWhoopee = 423,
        Mule = 414,
        NRG500 = 522,
        Nebula = 516,
        Nevada = 553,
        NewsMaverick = 488,
        Newsvan = 582,
        Oceanic = 467,
        PCJ600 = 461,
        Packer = 443,
        Patriot = 470,
        Perrenial = 404,
        Phoenix = 603,
        Picador = 600,
        Pizzaboy = 448,
        PoliceLasVenturas = 598,
        PoliceLosSantos = 596,
        PoliceMaverick = 497,
        PoliceRanger = 599,
        PoliceSanFierro = 597,
        Pony = 413,
        Predator = 430,
        Premier = 426,
        Previon = 436,
        Primo = 547,
        Quad = 471,
        RCBandit = 441,
        RCBaron = 464,
        RCCam = 594,
        RCGoblin = 501,
        RCRaider = 465,
        RCTiger = 564,
        Raindance = 563,
        Rancher = 489,
        Reefer = 453,
        Regina = 479,
        Remington = 534,
        Rhino = 432,
        Roadtrain = 515,
        Romero = 442,
        Rumpo = 440,
        Rustler = 476,
        Sabre = 475,
        Sadler = 543,
        Sanchez = 468,
        Sandking = 495,
        Savanna = 567,
        Seasparrow = 447,
        Securicar = 428,
        Sentinel = 405,
        Shamal = 519,
        Skimmer = 460,
        Slamvan = 535,
        Solair = 458,
        Sparrow = 469,
        Speeder = 452,
        Squallo = 446,
        Stafford = 580,
        Stallion = 439,
        Stratum = 561,
        Stretch = 409,
        StuntPlane = 513,
        Sultan = 560,
        Sunrise = 550,
        SuperGT = 506,
        SwatTank = 601,
        Sweeper = 574,
        SweeperTrailer = 611,
        Tahoma = 566,
        Tampa = 549,
        Tanker = 514,
        TankerTrailer = 584,
        Taxi = 420,
        Topfun = 459,
        Tornado = 576,
        Towtruck = 525,
        Tractor = 531,
        Trashmaster = 408,
        Tropic = 454,
        Tug = 583,
        TugStairs = 608,
        Turismo = 451,
        Uranus = 558,
        UtilityVan = 552,
        Vincent = 540,
        Virgo = 491,
        Voodoo = 412,
        Vortex = 539,
        Walton = 478,
        Washington = 421,
        Wayfarer = 586,
        Willard = 529,
        Windsor = 555,
        Yankee = 456,
        Yosemite = 554,
        ZR350 = 477
    }

    public enum WeaponID
    {
        Gift_Dildo1 = 10,
        Gift_Dildo2 = 11,
        Gift_Vibe1 = 12,
        Gift_Vibe2 = 13,
        Gift_Flowers = 14,
        Gift_Cane = 15,
        Melee_Unarmed = 0,
        Melee_BrassKnuckles = 1,
        Melee_GolfClub = 2,
        Melee_Nightstick = 3,
        Melee_Knife = 4,
        Melee_Bat = 5,
        Melee_Shovel = 6,
        Melee_PoolCue = 7,
        Melee_Katana = 8,
        Melee_Chainsaw = 9,
        Thrown_Grenades = 16,
        Thrown_Teargas = 17,
        Thrown_Molotovs = 18,
        Thrown_Satchel = 39,
        Satchel_Detonator = 40,
        Pistol_Colt45 = 22,
        Pistol_Silenced = 23,
        Pistol_Deagle = 24,
        Shotgun_Shotgun = 25,
        Shotgun_Sawnoff = 26,
        Shotgun_SPAS12 = 27,
        SMG_Uzi = 28,
        SMG_MP5 = 29,
        SMG_Tec9 = 32,
        Assault_AK47 = 30,
        Assault_M4 = 31,
        Rifle_Country = 33,
        Rifle_Sniper = 34,
        Heavy_RPG = 35,
        Heavy_HSRPG = 36,
        Heavy_Flamethrower = 37,
        Heavy_Minigun = 38,
        Misc_Spraycan = 41,
        Misc_FireExt = 42,
        Misc_Camera = 43,
        Apparel_NVGoggles = 44,
        Apparel_ThermGoggles = 45,
        Apparel_Parachute = 46
    }

    public enum BlipIcon
    {
        Misc_Destination = 0,
        Misc_WhiteSquare = 1,
        Misc_Player = 2,
        Misc_MenuArrow = 3,
        Misc_North = 4,
        Location_Airport = 5,
        Location_WeaponShop = 6,
        Location_Barber = 7,
        Person_BigSmoke = 8,
        Misc_Docks = 9,
        Location_Burger = 10,
        Location_Quarry = 11,
        Person_Catalina = 12,
        Person_CesarVialpando = 13,
        Location_CluckinBell = 14,
        Person_CarlJohnson = 15,
        Person_CRASH = 16,
        Activity_Dinner = 17,
        Misc_Emmet = 18,
        Misc_RedFlag = 19,
        Location_FireStation = 20,
        Misc_Girlfriend = 21,
        Location_Hospital = 22,
        Person_LocoSyndicate = 23,
        Person_MaddDogg = 24,
        Location_Calugulas = 25,
        Misc_STRAP = 26,
        Location_Tuning = 27,
        Person_OGLoc = 28,
        Location_Pizza = 29,
        Location_Police = 30,
        Misc_AssetBuyable = 31,
        Misc_AssetLocked = 32,
        Misc_Trophy = 33,
        Person_Ryder = 34,
        Misc_Save = 35,
        Location_School = 36,
        Person_UnknownContact = 37,
        Person_Sweet = 38,
        Location_Tattoo = 39,
        Person_Truth = 40,
        Misc_Target = 41,
        Person_Toreno = 42,
        Person_Triads = 43,
        Person_FourDragons = 44,
        Location_Clothes = 45,
        Person_Woozie = 46,
        Person_Zero = 47,
        Activity_Dance = 48,
        Activity_Drinking = 49,
        Activity_Restaurant = 50,
        Misc_Trucking = 51,
        Misc_Heist = 52,
        Misc_Race = 53,
        Location_Gym = 54,
        Misc_Car = 55,
        Misc_Light = 56,
        Misc_Runway = 57,
        Gang_Aztecas = 58,
        Gang_Ballas = 59,
        Gang_Vagos = 60,
        Gang_Rifa = 61,
        Gang_Grove = 62,
        Location_Sprayshop = 63
    }
}
