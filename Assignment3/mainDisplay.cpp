

//
// CST 407 - Assignment #3
//
// Michael Hoffman
//
// File: mainDisplay.cpp
//
// Display routines for the
// race analyzer main program.
//


#include  <iostream>
#include  <iomanip>
#include  <vector>
#include  <algorithm>
#include  <functional>
#include  <numeric>
#include  <iterator>
#include  "mainDisplay.h"

using  namespace  std;


#define  BASE_SECONDS  (3600.0)
#define  BASE_HOURS    (BASE_SECONDS / 3600.0)
//
// Used for distance calculations
//


#define  NUM_TEAM_RIDERS  3
//
// Number of rider's times to include when calculating the
// stage time for a team.
//


#define  ALL_STAGES   0   // indicates all race stages


//
// Used for calculating MPH
//
#define  SECS_PER_HOUR  3600
#define  SECS_PER_MIN   60


//
// Display field sizes, titles, and justify values
//

#define  FIELD_NAME_WIDTH  13
#define  FIELD_NAME_TITLE  "Name"
#define  FIELD_NAME_LEFT   true

#define  FIELD_TEAM_WIDTH  6
#define  FIELD_TEAM_TITLE  "Team"
#define  FIELD_TEAM_LEFT   true

#define  FIELD_COUNTRY_WIDTH  7
#define  FIELD_COUNTRY_TITLE  "Country"
#define  FIELD_COUNTRY_LEFT   true

#define  FIELD_SECONDS_WIDTH  10
#define  FIELD_SECONDS_TITLE  "  Time"
#define  FIELD_SECONDS_LEFT   true

#define  FIELD_MPH_WIDTH  7
#define  FIELD_MPH_TITLE  "  MPH"
#define  FIELD_MPH_LEFT   true



//
// Structure used to hold display parameters for rider data.
//
struct RiderDisplayParameters
{
	RiderDisplayParameters(const RaceAnalyzer &ra) : m_raceData(ra) {}

	const RaceAnalyzer  &m_raceData;
	unsigned             m_stage;
	string          m_team;
	string          m_country;
};


//
// Structure used to hold display parameters for team data.
//
struct TeamDisplayParameters
{
	TeamDisplayParameters(const RaceAnalyzer &ra) : m_raceData(ra) {}

	const RaceAnalyzer  &m_raceData;
	unsigned             m_stage;
};


typedef  pair<unsigned, string>  RowPair;
//
// Type for a row of column data. This is used for multi-column
// input choices.
//

typedef  set<RowPair>                 ColumnData;
//
// Set for multiple rows of column data. This is used for multi-column
// input choices.
//


//
// Prompt user for a display setting. The setting value is returned
// as a string. If the user hits return without entering a value,
// a zero-length string is returned. This indicates that "all"
// should be used for the value.
//
static string  getSetting(const char  *prompt)
{
	cout << endl << prompt << " (default: all) : ";

	string  userInput;

	getline(cin, userInput);

	return  userInput;
}


//
// Prompt the user for a stage number (or zero to indicate all stages),
// and validate the input.
//
int  getStageNumber(const RaceAnalyzer  &raceData)
{
	unsigned int  stageNum;

	while (true)
	{
		stageNum = atoi(getSetting("Stage #").c_str());

		if (stageNum <= raceData.numStages())
			break;

		cout << "Invalid number of stages!" << endl;
	}

	return  stageNum;
}


//
// Display the title for a field in an output table.
//
static void  displayTitle(unsigned  width, const string  &title, bool  leftJustify)
{
	cout << setw(width)
		<< (leftJustify ? left : right)
		<< title;
}


//
// Display the separator bar for a field in an output table.
//
static void  displaySeparator(unsigned  width)
{
	cout << setfill('-')
		<< setw(width)
		<< ""
		<< setfill(' ');
}


//
// Display the hour, minutes, seconds value given total
// number of seconds.
//
static void  displaySeconds(Seconds  seconds)
{
	unsigned  hours = seconds / SECS_PER_HOUR;

	seconds %= SECS_PER_HOUR;

	unsigned  minutes = seconds / SECS_PER_MIN;

	seconds %= SECS_PER_MIN;

	cout << setfill('0') << "  "
		<< setw(2) << right << hours << '"'
		<< setw(2) << right << minutes << '\''
		<< setw(2) << right << seconds
		<< setfill(' ');
}


//
// Display the MPH given a total seconds value and a stage
// number. The stage number is used to fetch the stage
// length for the calculation. A stage value of 0 indicates
// all stages.
//
static void  displayMPH(const RaceAnalyzer  &raceData,
	unsigned             stage,
	Seconds              seconds)
{
	cout << setprecision(4) << "  "
		<< setw(FIELD_MPH_WIDTH) << left << raceData.calcMPH(seconds, stage);
}


//
// Display table header for rider data.
//
void  displayRiderDataHeader(const RiderDisplayParameters  &params, unsigned  displayMax)
{
	//
	// Display table parameter information
	//
	cout << endl
		<< "**********" << endl
		<< endl
		<< "The following is data for ";


	if (displayMax)
		cout << "the first " << displayMax;
	else
		cout << "all";

	cout << " riders, for ";

	if (params.m_stage)
		cout << "stage #" << params.m_stage;
	else
		cout << "all stages";

	cout << ',' << endl << "for ";

	if (params.m_team.size())
		cout << "team " << params.m_team;
	else
		cout << "all teams";

	cout << ", for ";

	if (params.m_country.size())
		cout << "country " << params.m_country;
	else
		cout << "all countries";

	cout << '.' << endl << endl;


	//
	// Display Title
	//
	displayTitle(FIELD_NAME_WIDTH, FIELD_NAME_TITLE, FIELD_NAME_LEFT);

	if (!params.m_team.length())
		displayTitle(FIELD_TEAM_WIDTH, FIELD_TEAM_TITLE, FIELD_TEAM_LEFT);

	if (!params.m_country.length())
		displayTitle(FIELD_COUNTRY_WIDTH, FIELD_COUNTRY_TITLE, FIELD_COUNTRY_LEFT);

	displayTitle(FIELD_SECONDS_WIDTH, FIELD_SECONDS_TITLE, FIELD_SECONDS_LEFT);
	displayTitle(FIELD_MPH_WIDTH, FIELD_MPH_TITLE, FIELD_MPH_LEFT);


	//
	// Display Separator line
	//
	cout << endl;

	displaySeparator(FIELD_NAME_WIDTH);

	if (!params.m_team.length())
		displaySeparator(FIELD_TEAM_WIDTH);

	if (!params.m_country.length())
		displaySeparator(FIELD_COUNTRY_WIDTH);

	displaySeparator(FIELD_SECONDS_WIDTH);
	displaySeparator(FIELD_MPH_WIDTH);

	cout << endl;
}


//
// Functor to display data for a single rider
//
struct  DisplayRider : binary_function<RaceAnalyzer::PairResults, RiderDisplayParameters, bool>
{
	bool  operator()(const RaceAnalyzer::PairResults  &rider, const RiderDisplayParameters  &params)  const
	{
		const Seconds  &seconds = rider.first;
		const string   &name = rider.second;

		cout << setw(FIELD_NAME_WIDTH)
			<< (FIELD_NAME_LEFT ? left : right) << name;

		if (!params.m_team.length())
			cout << setw(FIELD_TEAM_WIDTH)
			<< (FIELD_TEAM_LEFT ? left : right) << params.m_raceData.getTeam(name);

		if (!params.m_country.length())
			cout << setw(FIELD_COUNTRY_WIDTH)
			<< (FIELD_COUNTRY_LEFT ? left : right) << params.m_raceData.getCountry(name);

		displaySeconds(seconds);
		displayMPH(params.m_raceData, params.m_stage, seconds);

		cout << endl;

		return  true;
	}
};


//
// Function object that can display information in multiple columns.
//
class  DisplayChoice
{
public:

	DisplayChoice(size_t              numRows,
		const string  &midStr) : m_numRows(numRows), m_midStr(midStr) {}

	void  operator()(const RowPair  &item)
	{
		unsigned  idx = item.first + (item.second > m_midStr ? m_numRows : 0);

		cout << "     " << setw(2) << idx
			<< ". " << item.second;

		if (item.second > m_midStr)
			cout << endl;
	}

private:

	const size_t       m_numRows;
	const string  m_midStr;
};


//
// Converts string data to pairs of row numbers and strings.
//
class  StrToRowPair
{
public:

	StrToRowPair(size_t  numRows) : m_numRows(numRows), m_curRow(1) {}

	RowPair  operator()(const string  &str)
	{
		RowPair  result(Seconds(m_curRow++), str);

		if (m_curRow > m_numRows)
			m_curRow = 1;

		return  result;
	}

private:

	const size_t  m_numRows;
	size_t  m_curRow;
};


//
// Builds a container made up of rows, each of which has multiple
// columns. This is used for multi-column choice lists.
//
static  ColumnData  buildColumnData(const RaceAnalyzer::StrSet  &data, size_t  numRows)
{
	ColumnData  result;

	transform(data.begin(),
		data.end(),
		inserter(result, result.end()),
		StrToRowPair(numRows));

	return  result;
}


//
// Generates and displays a two-column list of choices for the use
// to choose from. The return value is the string the user has chosen.
//
static  string  getSettingByList(const RaceAnalyzer::StrSet  &data,
	const char                  *prompt)
{
	cout << endl;

	//
	// Determine how many rows there will be in the 2-column display
	//
	size_t  numRows = (data.size() / 2) + (data.size() % 2);

	//
	// Generate the container of row/string data
	//
	ColumnData  columnData = buildColumnData(data, numRows);


	//
	// Display the multi-column choice list.
	//
	RaceAnalyzer::StrSet::const_iterator  midIter = data.begin();
	advance(midIter, numRows - 1);

	for_each(columnData.begin(), columnData.end(), DisplayChoice(numRows, *midIter));

	if (data.size() % 2)
		cout << endl;


	//
	// Get (and validate) the user's choice
	//
	unsigned  num;

	while (true)
	{
		string  numStr = getSetting(prompt);

		if (!numStr.size())   // blank indicates "all"
			return  numStr;

		num = atoi(numStr.c_str());

		if (num >= 1 && num <= data.size())
			break;

		cout << endl
			<< "  *** Invalid number. Try Again. ***"
			<< endl;
	}


	//
	// Return the chosen string from the user's numeric input.
	//
	RaceAnalyzer::StrSet::const_iterator  iter = data.begin();

	advance(iter, num - 1);

	return  *iter;
}


//
// Displays rider data.
//
void  displayRiderData(const RaceAnalyzer  &raceData)
{
	cout << endl;

	//
	// Get display parameters from the user
	//

	RiderDisplayParameters  displayParams(raceData);

	displayParams.m_stage = getStageNumber(raceData);

	displayParams.m_team = getSettingByList(raceData.teams(), "Team #");
	displayParams.m_country = getSettingByList(raceData.countries(), "Country #");

	unsigned     displayMax = atoi(getSetting("Display max").c_str());


	//
	// Display the table header
	//
	displayRiderDataHeader(displayParams, displayMax);


	//
	// Get the rider data
	//
	RaceAnalyzer::Results  riders = raceData.riderResults(displayParams.m_stage, displayParams.m_team, displayParams.m_country);


	//
	// Handle no matching results
	//
	if (!riders.size())
	{
		cout << "*** no riders match the selected criteria ***" << endl;
		return;
	}

	//
	// Pair down the data so there is only as much as the
	// user wants to see.
	//
	if (displayMax  &&  displayMax <= riders.size())
	{
		RaceAnalyzer::Results::iterator  iter;

		iter = riders.begin();

		advance(iter, displayMax);

		riders.erase(iter, riders.end());
	}


	//
	// Display the rider data
	//
	for_each(riders.begin(), riders.end(), bind2nd(DisplayRider(), displayParams));
}


//
// Display table header for team data.
//
void  displayTeamDataHeader(const TeamDisplayParameters  &params, unsigned  displayMax)
{
	//
	// Display table parameter information
	//

	cout << endl
		<< "**********" << endl
		<< endl
		<< "The following is data for ";


	if (displayMax)
		cout << "the first " << displayMax;
	else
		cout << "all";

	cout << " teams, for ";

	if (params.m_stage)
		cout << "stage #" << params.m_stage;
	else
		cout << "all stages";

	cout << '.' << endl << endl;


	//
	// Display Title
	//

	displayTitle(FIELD_TEAM_WIDTH, FIELD_TEAM_TITLE, FIELD_TEAM_LEFT);
	displayTitle(FIELD_SECONDS_WIDTH, FIELD_SECONDS_TITLE, FIELD_SECONDS_LEFT);


	//
	// Display Separator line
	//
	cout << endl;

	displaySeparator(FIELD_TEAM_WIDTH);
	displaySeparator(FIELD_SECONDS_WIDTH + 1);

	cout << endl;
}


//
// Functor to display data for a single team
//
struct  DisplayTeam : binary_function<RaceAnalyzer::PairResults, TeamDisplayParameters, bool>
{
	bool  operator()(const RaceAnalyzer::PairResults  &data, const TeamDisplayParameters  &params)  const
	{
		const Seconds  &seconds = data.first;
		const string   &team = data.second;

		cout << setw(FIELD_TEAM_WIDTH)
			<< (FIELD_TEAM_LEFT ? left : right) << team;

		displaySeconds(seconds);

		cout << endl;

		return  true;
	}
};


//
// Function object to convert a team name into a
// seconds/name pair.
//
class  TeamToTeamResult : public  binary_function< string, RaceAnalyzer, RaceAnalyzer::PairResults >
{
public:

	TeamToTeamResult(unsigned  stage) : m_stage(stage) {}

	RaceAnalyzer::PairResults  operator()(const string  &team, const RaceAnalyzer  &raceData)  const
	{
		Seconds  seconds = raceData.teamTime(team, m_stage, NUM_TEAM_RIDERS);

		return  RaceAnalyzer::PairResults(seconds, team);
	}

private:

	unsigned  m_stage;
};


//
// Displays team data.
//
void  displayTeamData(const RaceAnalyzer  &raceData)
{
	cout << endl;

	//
	// Get display parameters from the user
	//

	TeamDisplayParameters  displayParams(raceData);

	displayParams.m_stage = getStageNumber(raceData);

	unsigned     displayMax = atoi(getSetting("Display max").c_str());


	//
	// Display the table header
	//
	displayTeamDataHeader(displayParams, displayMax);


	//
	// Get the team names
	//
	RaceAnalyzer::StrSet  teams = raceData.teams();



	//
	// Create (or sort) a container of team seconds/name
	//
	RaceAnalyzer::Results  teamResults;

	transform(teams.begin(),
		teams.end(),
		back_inserter(teamResults),
		bind2nd(TeamToTeamResult(displayParams.m_stage), raceData));


	teamResults.sort();


	//
	// Handle no matching results
	//
	if (!teamResults.size())
	{
		cout << "*** no teams match the selected criteria ***" << endl;
		return;
	}


	//
	// Pair down the data so there is only as much as the
	// user wants to see.
	//
	if (displayMax)
	{
		RaceAnalyzer::Results::iterator  iter = teamResults.begin();

		advance(iter, displayMax);

		teamResults.erase(iter, teamResults.end());
	}


	//
	// Display the team data
	//
	for_each(teamResults.begin(),
		teamResults.end(),
		bind2nd(DisplayTeam(), displayParams));
}


//
// Function object to calculate the distance for race stages.
//
class  StageDistance : unary_function<RaceAnalyzer, double>
{
public:

	StageDistance(const RaceAnalyzer  &raceData) : m_raceData(raceData), m_stageNum(1) {}

	double  operator()()
	{
		return  m_raceData.calcMPH(Seconds(BASE_SECONDS), m_stageNum++) * BASE_HOURS;
	}

private:

	const RaceAnalyzer  &m_raceData;

	unsigned  m_stageNum;
};


//
// Determine the total race distance
//
static double  calcTotalDistance(const RaceAnalyzer  &raceData)
{
	//
	// Create and populate a vector that contains the distances for
	// each of the stages. Then add up the distances.
	//

	vector<double>  distances(raceData.numStages());

	generate(distances.begin(), distances.end(), StageDistance(raceData));

	return  accumulate(distances.begin(), distances.end(), 0.0);
}


//
// Displays summary info
//
void  displaySummary(const RaceAnalyzer  &raceData)
{
	//
	// Get all race times for all riders
	//
	const RaceAnalyzer::Results  riders = raceData.riderResults(0, "", "");

	//
	// Determine the fastest rider
	//
	RaceAnalyzer::Results::const_iterator  fastest = min_element(riders.begin(),
		riders.end());

	const Seconds  &fastestSeconds = fastest->first;
	const string   &fastestRider = fastest->second;


	//
	// Dispaly summary info
	//
	cout << endl
		<< "***********************" << endl
		<< endl
		<< "      # of stages  :  " << raceData.numStages() << endl
		<< "      total miles  :  " << setprecision(10) << calcTotalDistance(raceData) << endl
		<< "      # of riders  :  " << riders.size() << endl
		<< "       # of teams  :  " << raceData.teams().size() << endl
		<< "   # of countries  :  " << raceData.countries().size() << endl
		<< endl
		<< "    Fastest rider  :  " << fastestRider << endl
		<< "     Fastest time  :";

	displaySeconds(fastestSeconds);

	cout << endl
		<< "  Fastest avg MPH  :";

	displayMPH(raceData, 0, fastestSeconds);

	cout << endl;
}