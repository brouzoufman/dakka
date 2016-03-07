#define DAKKASPREAD_ENTRIES     513

// cumulative normal distribution over the range [-1.0, 1.0]
//
// infinities chopped off, max values used to normalize the array
//
// this table is here to speed up spread lookups
int Dakka_SpreadTable[DAKKASPREAD_ENTRIES] =
{
    -1.000000, -0.921894, -0.873569, -0.837926, -0.809423, -0.785531, -0.764879, -0.746633, -0.730251, -0.715355, -0.701676, -0.689010, -0.677204, -0.666136, -0.655709, -0.645844,
    -0.636477, -0.627553, -0.619027, -0.610861, -0.603021, -0.595478, -0.588207, -0.581186, -0.574397, -0.567821, -0.561444, -0.555251, -0.549231, -0.543373, -0.537665, -0.532101,
    -0.526670, -0.521366, -0.516181, -0.511109, -0.506145, -0.501282, -0.496516, -0.491843, -0.487257, -0.482755, -0.478333, -0.473988, -0.469716, -0.465515, -0.461380, -0.457311,
    -0.453304, -0.449356, -0.445466, -0.441631, -0.437850, -0.434120, -0.430440, -0.426808, -0.423222, -0.419681, -0.416183, -0.412727, -0.409312, -0.405936, -0.402598, -0.399297,
    -0.396032, -0.392802, -0.389606, -0.386442, -0.383310, -0.380210, -0.377139, -0.374098, -0.371086, -0.368101, -0.365143, -0.362212, -0.359306, -0.356426, -0.353570, -0.350738,
    -0.347929, -0.345143, -0.342378, -0.339636, -0.336915, -0.334214, -0.331533, -0.328872, -0.326231, -0.323608, -0.321004, -0.318418, -0.315849, -0.313297, -0.310763, -0.308245,
    -0.305743, -0.303257, -0.300787, -0.298331, -0.295891, -0.293465, -0.291054, -0.288656, -0.286273, -0.283903, -0.281546, -0.279202, -0.276870, -0.274551, -0.272245, -0.269950,
    -0.267667, -0.265396, -0.263136, -0.260888, -0.258650, -0.256423, -0.254206, -0.252000, -0.249804, -0.247618, -0.245442, -0.243276, -0.241119, -0.238971, -0.236832, -0.234703,
    -0.232582, -0.230470, -0.228366, -0.226271, -0.224184, -0.222105, -0.220035, -0.217972, -0.215916, -0.213869, -0.211828, -0.209795, -0.207770, -0.205751, -0.203739, -0.201734,
    -0.199736, -0.197745, -0.195760, -0.193781, -0.191809, -0.189843, -0.187883, -0.185929, -0.183981, -0.182038, -0.180102, -0.178171, -0.176245, -0.174325, -0.172411, -0.170501,
    -0.168597, -0.166698, -0.164804, -0.162915, -0.161030, -0.159150, -0.157275, -0.155405, -0.153539, -0.151678, -0.149821, -0.147968, -0.146119, -0.144275, -0.142435, -0.140598,
    -0.138766, -0.136938, -0.135113, -0.133292, -0.131475, -0.129661, -0.127851, -0.126044, -0.124241, -0.122441, -0.120645, -0.118851, -0.117061, -0.115274, -0.113490, -0.111709,
    -0.109931, -0.108156, -0.106384, -0.104615, -0.102848, -0.101084, -0.099322, -0.097563, -0.095807, -0.094053, -0.092302, -0.090553, -0.088806, -0.087061, -0.085319, -0.083578,
    -0.081840, -0.080104, -0.078370, -0.076638, -0.074908, -0.073180, -0.071453, -0.069728, -0.068005, -0.066284, -0.064564, -0.062846, -0.061130, -0.059415, -0.057701, -0.055989,
    -0.054278, -0.052569, -0.050860, -0.049153, -0.047448, -0.045743, -0.044040, -0.042337, -0.040636, -0.038935, -0.037236, -0.035537, -0.033839, -0.032142, -0.030446, -0.028751,
    -0.027056, -0.025362, -0.023668, -0.021975, -0.020283, -0.018591, -0.016899, -0.015208, -0.013518, -0.011827, -0.010137, -0.008447, -0.006758, -0.005068, -0.003379, -0.001689,
     0.000000,
     0.001689,  0.003379,  0.005068,  0.006758,  0.008447,  0.010137,  0.011827,  0.013518,  0.015208,  0.016899,  0.018591,  0.020283,  0.021975,  0.023668,  0.025362,  0.027056,
     0.028751,  0.030446,  0.032142,  0.033839,  0.035537,  0.037236,  0.038935,  0.040636,  0.042337,  0.044040,  0.045743,  0.047448,  0.049153,  0.050860,  0.052569,  0.054278,
     0.055989,  0.057701,  0.059415,  0.061130,  0.062846,  0.064564,  0.066284,  0.068005,  0.069728,  0.071453,  0.073180,  0.074908,  0.076638,  0.078370,  0.080104,  0.081840,
     0.083578,  0.085319,  0.087061,  0.088806,  0.090553,  0.092302,  0.094053,  0.095807,  0.097563,  0.099322,  0.101084,  0.102848,  0.104615,  0.106384,  0.108156,  0.109931,
     0.111709,  0.113490,  0.115274,  0.117061,  0.118851,  0.120645,  0.122441,  0.124241,  0.126044,  0.127851,  0.129661,  0.131475,  0.133292,  0.135113,  0.136938,  0.138766,
     0.140598,  0.142435,  0.144275,  0.146119,  0.147968,  0.149821,  0.151678,  0.153539,  0.155405,  0.157275,  0.159150,  0.161030,  0.162915,  0.164804,  0.166698,  0.168597,
     0.170501,  0.172411,  0.174325,  0.176245,  0.178171,  0.180102,  0.182038,  0.183981,  0.185929,  0.187883,  0.189843,  0.191809,  0.193781,  0.195760,  0.197745,  0.199736,
     0.201734,  0.203739,  0.205751,  0.207770,  0.209795,  0.211828,  0.213869,  0.215916,  0.217972,  0.220035,  0.222105,  0.224184,  0.226271,  0.228366,  0.230470,  0.232582,
     0.234703,  0.236832,  0.238971,  0.241119,  0.243276,  0.245442,  0.247618,  0.249804,  0.252000,  0.254206,  0.256423,  0.258650,  0.260888,  0.263136,  0.265396,  0.267667,
     0.269950,  0.272245,  0.274551,  0.276870,  0.279202,  0.281546,  0.283903,  0.286273,  0.288656,  0.291054,  0.293465,  0.295891,  0.298331,  0.300787,  0.303257,  0.305743,
     0.308245,  0.310763,  0.313297,  0.315849,  0.318418,  0.321004,  0.323608,  0.326231,  0.328872,  0.331533,  0.334214,  0.336915,  0.339636,  0.342378,  0.345143,  0.347929,
     0.350738,  0.353570,  0.356426,  0.359306,  0.362212,  0.365143,  0.368101,  0.371086,  0.374098,  0.377139,  0.380210,  0.383310,  0.386442,  0.389606,  0.392802,  0.396032,
     0.399297,  0.402598,  0.405936,  0.409312,  0.412727,  0.416183,  0.419681,  0.423222,  0.426808,  0.430440,  0.434120,  0.437850,  0.441631,  0.445466,  0.449356,  0.453304,
     0.457311,  0.461380,  0.465515,  0.469716,  0.473988,  0.478333,  0.482755,  0.487257,  0.491843,  0.496516,  0.501282,  0.506145,  0.511109,  0.516181,  0.521366,  0.526670,
     0.532101,  0.537665,  0.543373,  0.549231,  0.555251,  0.561444,  0.567821,  0.574397,  0.581186,  0.588207,  0.595478,  0.603021,  0.610861,  0.619027,  0.627553,  0.636477,
     0.645844,  0.655709,  0.666136,  0.677204,  0.689010,  0.701676,  0.715355,  0.730251,  0.746633,  0.764879,  0.785531,  0.809423,  0.837926,  0.873569,  0.921894,  1.000000,
} ;


script "Dakka_Spread" (int x, int y)
{
    int hi = itof(max(x,y)) / 100;
    int lo = itof(min(x,y)) / 100;

    int range  = hi - lo;
    int center = lo + (range / 2);

    int rand = random(0, 1.0);
    int randIndex = round(rand * (DAKKASPREAD_ENTRIES - 1));

    int ret = FixedMul(range / 2, Dakka_SpreadTable[randIndex]) + center;

    SetResultValue(ret);
}

