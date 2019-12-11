﻿namespace GTA
{
    public enum VehicleLock
    {
        Unlocked = 1,
        Locked = 2,
        Unknown3 = 3,
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
        UsjPassed = 0x2B,
        Menu1 = 0x23,
        TimerEnd = 0x21
    }

    public enum PedId : int
    {
        Null = 0,
        Male01 = 7,
        Bfori = 9,
        Bfost = 10,
        Vbfycrp = 11,
        Bfyri = 12,
        Bfyst = 13,
        Bmori = 14,
        Bmost = 15,
        Bmyap = 16,
        Bmybu = 17,
        Bmybe = 18,
        Bmydj = 19,
        Bmyri = 20,
        Bmycr = 21,
        Bmyst = 22,
        Wmybmx = 23,
        Wbdyg1 = 24,
        Wbdyg2 = 25,
        Wmybp = 26,
        Wmycon = 27,
        Bmydrug = 28,
        Wmydrug = 29,
        Hmydrug = 30,
        Dwfolc = 31,
        Dwmolc1 = 32,
        Dwmolc2 = 33,
        Dwmylc1 = 34,
        Hmogar = 35,
        Wmygol1 = 36,
        Wmygol2 = 37,
        Hfori = 38,
        Hfost = 39,
        Hfyri = 40,
        Hfyst = 41,
        Hmori = 43,
        Hmost = 44,
        Hmybe = 45,
        Hmyri = 46,
        Hmycr = 47,
        Hmyst = 48,
        Omokung = 49,
        Wmymech = 50,
        Bmymoun = 51,
        Wmymoun = 52,
        Ofori = 53,
        Ofost = 54,
        Ofyri = 55,
        Ofyst = 56,
        Omori = 57,
        Omost = 58,
        Omyri = 59,
        Omyst = 60,
        Wmyplt = 61,
        Wmopj = 62,
        Bfypro = 63,
        Hfypro = 64,
        Bmypol1 = 66,
        Bmypol2 = 67,
        Wmoprea = 68,
        Sbfyst = 69,
        Wmosci = 70,
        Wmysgrd = 71,
        Swmyhp1 = 72,
        Swmyhp2 = 73,
        Swfopro = 75,
        Wfystew = 76,
        Swmotr1 = 77,
        Wmotr1 = 78,
        Bmotr1 = 79,
        Vbmybox = 80,
        Vwmybox = 81,
        Vhmyelv = 82,
        Vbmyelv = 83,
        Vimyelv = 84,
        Vwfypro = 85,
        Vwfyst1 = 87,
        Wfori = 88,
        Wfost = 89,
        Wfyjg = 90,
        Wfyri = 91,
        Wfyro = 92,
        Wfyst = 93,
        Wmori = 94,
        Wmost = 95,
        Wmyjg = 96,
        Wmylg = 97,
        Wmyri = 98,
        Wmyro = 99,
        Wmycr = 100,
        Wmyst = 101,
        Ballas1 = 102,
        Ballas2 = 103,
        Ballas3 = 104,
        Fam1 = 105,
        Fam2 = 106,
        Fam3 = 107,
        Lsv1 = 108,
        Lsv2 = 109,
        Lsv3 = 110,
        Maffa = 111,
        Maffb = 112,
        Mafboss = 113,
        Vla1 = 114,
        Vla2 = 115,
        Vla3 = 116,
        Triada = 117,
        Triadb = 118,
        Triboss = 120,
        Dnb1 = 121,
        Dnb2 = 122,
        Dnb3 = 123,
        Vmaff1 = 124,
        Vmaff2 = 125,
        Vmaff3 = 126,
        Vmaff4 = 127,
        Dnmylc = 128,
        Dnfolc1 = 129,
        Dnfolc2 = 130,
        Dnfylc = 131,
        Dnmolc1 = 132,
        Dnmolc2 = 133,
        Sbmotr2 = 134,
        Swmotr2 = 135,
        Sbmytr3 = 136,
        Swmotr3 = 137,
        Wfybe = 138,
        Bfybe = 139,
        Hfybe = 140,
        Sofybu = 141,
        Sbmyst = 142,
        Sbmycr = 143,
        Bmycg = 144,
        Wfycrk = 145,
        Hmycm = 146,
        Wmybu = 147,
        Bfybu = 148,
        Wfybu = 150,
        Dwfylc1 = 151,
        Wfypro = 152,
        Wmyconb = 153,
        Wmybe = 154,
        Wmypizz = 155,
        Bmobar = 156,
        Cwfyhb = 157,
        Cwmofr = 158,
        Cwmohb1 = 159,
        Cwmohb2 = 160,
        Cwmyfr = 161,
        Cwmyhb1 = 162,
        Bmyboun = 163,
        Wmyboun = 164,
        Wmomib = 165,
        Bmymib = 166,
        Wmybell = 167,
        Bmochil = 168,
        Sofyri = 169,
        Somyst = 170,
        Vwmybjd = 171,
        Vwfycrp = 172,
        Sfr1 = 173,
        Sfr2 = 174,
        Sfr3 = 175,
        Bmybar = 176,
        Wmybar = 177,
        Wfysex = 178,
        Wmyammo = 179,
        Bmytatt = 180,
        Vwmycr = 181,
        Vbmocd = 182,
        Vbmycr = 183,
        Vhmycr = 184,
        Sbmyri = 185,
        Somyri = 186,
        Somybu = 187,
        Swmyst = 188,
        Wmyva = 189,
        Copgrl3 = 190,
        Gungrl3 = 191,
        Mecgrl3 = 192,
        Nurgrl3 = 193,
        Crogrl3 = 194,
        Gangrl3 = 195,
        Cwfofr = 196,
        Cwfohb = 197,
        Cwfyfr1 = 198,
        Cwfyfr2 = 199,
        Cwmyhb2 = 200,
        Dwfylc2 = 201,
        Dwmylc2 = 202,
        Omykara = 203,
        Wmykara = 204,
        Wfyburg = 205,
        Vwmycd = 206,
        Vhfypro = 207,
        Omonood = 209,
        Omoboat = 210,
        Wfyclot = 211,
        Vwmotr1 = 212,
        Vwmotr2 = 213,
        Vwfywai = 214,
        Sbfori = 215,
        Swfyri = 216,
        Wmyclot = 217,
        Sbfost = 218,
        Sbfyri = 219,
        Sbmocd = 220,
        Sbmori = 221,
        Sbmost = 222,
        Shmycr = 223,
        Sofori = 224,
        Sofost = 225,
        Sofyst = 226,
        Somobu = 227,
        Somori = 228,
        Somost = 229,
        Swmotr5 = 230,
        Swfori = 231,
        Swfost = 232,
        Swfyst = 233,
        Swmocd = 234,
        Swmori = 235,
        Swmost = 236,
        Shfypro = 237,
        Sbfypro = 238,
        Swmotr4 = 239,
        Swmyri = 240,
        Smyst = 241,
        Smyst2 = 242,
        Sfypro = 243,
        Vbfyst2 = 244,
        Vbfypro = 245,
        Vhfyst3 = 246,
        Bikera = 247,
        Bikerb = 248,
        Bmypimp = 249,
        Swmycr = 250,
        Wfylg = 251,
        Wmyva2 = 252,
        Bmosec = 253,
        Bikdrug = 254,
        Wmych = 255,
        Sbfystr = 256,
        Swfystr = 257,
        Heck1 = 258,
        Heck2 = 259,
        Bmycon = 260,
        Wmycd1 = 261,
        Bmocd = 262,
        Vwfywa2 = 263,
        Wmoice = 264,
        Laemt1 = 274,
        Lvemt1 = 275,
        Sfemt1 = 276,
        Lafd1 = 277,
        Lvfd1 = 278,
        Sffd1 = 279,
        Lapd1 = 280,
        Sfpd1 = 281,
        Lvpd1 = 282,
        Csher = 283,
        Lapdm1 = 284,
        Swat = 285,
        Fbi = 286,
        Army = 287,
        Dsher = 288,
        Special01 = 290,
        Special02 = 291,
        Special03 = 292,
        Special04 = 293,
        Special05 = 294,
        Special06 = 295,
        Special07 = 296,
        Special08 = 297,
        Special09 = 298,
        Special10 = 299
    }

    public enum CarId
    {
        At400 = 577,
        Admiral = 445,
        Alpha = 602,
        Ambulance = 416,
        Andromada = 592,
        Artict1 = 435,
        Artict2 = 450,
        Artict3 = 591,
        Bf400 = 581,
        BfInjection = 424,
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
        Dft30 = 578,
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
        FbiRancher = 490,
        FbiTruck = 528,
        Fcr900 = 521,
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
        Hpv1000 = 523,
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
        Nrg500 = 522,
        Nebula = 516,
        Nevada = 553,
        NewsMaverick = 488,
        Newsvan = 582,
        Oceanic = 467,
        Pcj600 = 461,
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
        RcBandit = 441,
        RcBaron = 464,
        RcCam = 594,
        RcGoblin = 501,
        RcRaider = 465,
        RcTiger = 564,
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
        SuperGt = 506,
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
        Zr350 = 477
    }

    public enum WeaponId
    {
        GiftDildo1 = 10,
        GiftDildo2 = 11,
        GiftVibe1 = 12,
        GiftVibe2 = 13,
        GiftFlowers = 14,
        GiftCane = 15,
        MeleeUnarmed = 0,
        MeleeBrassKnuckles = 1,
        MeleeGolfClub = 2,
        MeleeNightstick = 3,
        MeleeKnife = 4,
        MeleeBat = 5,
        MeleeShovel = 6,
        MeleePoolCue = 7,
        MeleeKatana = 8,
        MeleeChainsaw = 9,
        ThrownGrenades = 16,
        ThrownTeargas = 17,
        ThrownMolotovs = 18,
        ThrownSatchel = 39,
        SatchelDetonator = 40,
        PistolColt45 = 22,
        PistolSilenced = 23,
        PistolDeagle = 24,
        ShotgunShotgun = 25,
        ShotgunSawnoff = 26,
        ShotgunSpas12 = 27,
        SmgUzi = 28,
        SmgMp5 = 29,
        SmgTec9 = 32,
        AssaultAk47 = 30,
        AssaultM4 = 31,
        RifleCountry = 33,
        RifleSniper = 34,
        HeavyRpg = 35,
        HeavyHsrpg = 36,
        HeavyFlamethrower = 37,
        HeavyMinigun = 38,
        MiscSpraycan = 41,
        MiscFireExt = 42,
        MiscCamera = 43,
        ApparelNvGoggles = 44,
        ApparelThermGoggles = 45,
        ApparelParachute = 46
    }

    public enum BlipIcon
    {
        MiscDestination = 0,
        MiscWhiteSquare = 1,
        MiscPlayer = 2,
        MiscMenuArrow = 3,
        MiscNorth = 4,
        LocationAirport = 5,
        LocationWeaponShop = 6,
        LocationBarber = 7,
        PersonBigSmoke = 8,
        MiscDocks = 9,
        LocationBurger = 10,
        LocationQuarry = 11,
        PersonCatalina = 12,
        PersonCesarVialpando = 13,
        LocationCluckinBell = 14,
        PersonCarlJohnson = 15,
        PersonCrash = 16,
        ActivityDinner = 17,
        MiscEmmet = 18,
        MiscRedFlag = 19,
        LocationFireStation = 20,
        MiscGirlfriend = 21,
        LocationHospital = 22,
        PersonLocoSyndicate = 23,
        PersonMaddDogg = 24,
        LocationCalugulas = 25,
        MiscStrap = 26,
        LocationTuning = 27,
        PersonOgLoc = 28,
        LocationPizza = 29,
        LocationPolice = 30,
        MiscAssetBuyable = 31,
        MiscAssetLocked = 32,
        MiscTrophy = 33,
        PersonRyder = 34,
        MiscSave = 35,
        LocationSchool = 36,
        PersonUnknownContact = 37,
        PersonSweet = 38,
        LocationTattoo = 39,
        PersonTruth = 40,
        MiscTarget = 41,
        PersonToreno = 42,
        PersonTriads = 43,
        PersonFourDragons = 44,
        LocationClothes = 45,
        PersonWoozie = 46,
        PersonZero = 47,
        ActivityDance = 48,
        ActivityDrinking = 49,
        ActivityRestaurant = 50,
        MiscTrucking = 51,
        MiscHeist = 52,
        MiscRace = 53,
        LocationGym = 54,
        MiscCar = 55,
        MiscLight = 56,
        MiscRunway = 57,
        GangAztecas = 58,
        GangBallas = 59,
        GangVagos = 60,
        GangRifa = 61,
        GangGrove = 62,
        LocationSprayshop = 63
    }
}
