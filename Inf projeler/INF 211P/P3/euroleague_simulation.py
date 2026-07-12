my_name = 'Student Name'
my_id = '00000000000'
my_email = 'student@gtu.edu.tr'
import random
class Person:
    def __init__(self, name, lastname):
        self.name = name
        self.lastname = lastname

    def get_name(self):
        return self.name + ' ' + self.lastname

    def __str__(self):
        return self.get_name()

    def __lt__(self, other):
        if self.lastname == other.lastname:
            return self.name < other.name
        return self.lastname < other.lastname
              
class Player(Person):
    player_id_counter = 1
    
    def __init__(self, name, lastname):
        super().__init__(name, lastname)
        self.player_id = Player.player_id_counter
        Player.player_id_counter += 1
        self.shooting_power = random.randint(4, 8)
        self.points = []
        self.team = None
    
    def reset(self):
        self.points = []
    
    def get_id(self):
        return self.player_id
    
    def get_power(self):
        return self.shooting_power
    
    def set_team(self, team):
        self.team = team
    
    def get_team(self):
        return self.team
    
    def add_to_points(self, x):
        self.points.append(x)
    
    def get_points_detailed(self):
        return self.points
    
    def get_points(self):
        return sum(self.points)
    
    def __lt__(self, other):
        if self.get_points() != other.get_points():
            return self.get_points() < other.get_points()
        if self.get_points() != other.get_points():
            if self.lastname != other.lastname:
                return self.lastname < other.lastname
        else:
            return self.name < other.name

class Manager(Person):
    manager_counter = 1

    def __init__(self, name, lastname):
        super().__init__(name, lastname)
        self.influence_points = []
        self.team = None
        self.manager_id = Manager.generate_manager_id()

    def reset(self):
        super().reset()
        self.influence_points = []
    def get_id(self):
        return self.manager_id

    def set_team(self, team):
        self.team = team

    def get_team(self):
        return self.team

    def add_to_influence_detailed(self, points): #Upsi 
        self.influence_points.append(points)

    def get_influence_detailed(self):
        return self.influence_points

    def get_influence(self):
        return sum(self.get_influence_detailed())

    def __lt__(self, other):
        if self.get_influence() != other.get_influence():
            return self.get_influence() < other.get_influence()
        elif self.lastname != other.lastname:
            return self.lastname < other.lastname
        else:
            return self.name < other.name


    @classmethod
    def generate_manager_id(cls):
        cls.manager_counter += 1
        return cls.manager_counter
 
class Team:
    team_counter = 1

    def __init__(self, teamname, manager, players):
        Team.team_counter += 1
        self.team_id = Team.team_counter
        self.teamname = teamname
        self.manager = manager
        self.players = list(players)
        self.matches = []
        self.wins = 0
        self.scored = 0
        self.conceded = 0

    def reset(self):
        self.manager.reset()
        for player in self.players:
            player.reset()
        self.matches = []
        self.wins = 0
        self.scored = 0
        self.conceded = 0

    def get_id(self):
        return self.team_id

    def get_name(self):
        return self.teamname

    def get_roster(self):
        return self.players

    def get_manager(self):
        return self.manager

    def add_to_fixture(self, m):
        self.matches.append(m)

    def get_fixture(self):
        return self.matches

    def add_result(self, result):
        own_score, opp_score = result
        self.scored += own_score
        self.conceded += opp_score
        if own_score > opp_score:
            self.wins += 1

    def get_scored(self):
        return self.scored

    def get_conceded(self):
        return self.conceded

    def get_wins(self):
        return self.wins

    def get_losses(self):
        return len(self.matches) - self.wins

    def add_players(self, players): #Extra 
        self.players.extend(players)
    
    def __str__(self):
        return self.teamname

    def __lt__(self, other):
        if self.get_wins() != other.get_wins():
            return self.get_wins() < other.get_wins()
        elif self.get_total_score() != other.get_total_score():
            return self.get_total_score() < other.get_total_score()
        else:
            return True 


    def get_total_score(self): #Extra
        return sum([match.get_team_score(self) for match in self.matches])

"""inst = Player('Dimitris', 'Diamantidis')
inst2 = Player('Juan Carlos', 'Navarro')
fb_players = [Player('Jan', 'Vesely'),
Player('Achille', 'Polonara'),
Player('Marko', 'Guduric'),
Player('Marial', 'Shayok'), 
Player('Nandode', 'Colo')]
fb_manager = Manager('Sasa', 'Dordevic')
print(inst.get_id())  # Output: 1
print(inst.get_power())  # Output: random number between 4 and 8
team = Team('Fenerbahce', fb_manager, fb_players)
inst.set_team(team)
print(inst.get_team())  # Output: Fenerbahce
inst.add_to_points(30)
inst.add_to_points(35)
print(inst.get_points_detailed())  # Output: [30, 35]
print(inst.get_points())  # Output: 65
print(inst < inst2)  # Output: True"""

"""# Create players
player1 = Player('Jan', 'Vesely')
player2 = Player('Achille', 'Polonara')
player3 = Player('Marko', 'Guduric')
player4 = Player('Marial', 'Shayok')
player5 = Player('Nando', 'de Colo')

# Create a manager
manager = Manager('Sasa', 'Dordevic')

# Create a team
team = Team('Fenerbahce Beko Istanbul', manager, [player1, player2, player3, player4, player5])

# Get and print the team ID
print("Team ID:", team.get_id())  # Output: 1

# Create another team
team2 = Team('Opponent Team', Manager('Opponent', 'Manager'), [Player('Opponent', 'Player1'), Player('Opponent', 'Player2'), Player('Opponent', 'Player3'), Player('Opponent', 'Player4'), Player('Opponent', 'Player5')])

# Get and print the second team ID
print("Team ID:", team2.get_id())  # Output: 2
"""
class Match:
    def __init__(self, home_team, away_team, week_no =6):
        self.home_team = home_team
        self.away_team = away_team
        self.week_no = week_no
        self.played = False
        self.match_score = None

    def is_played(self):
        return self.played

    def play(self):
        if self.played:
            return
        home_manager_point = random.randint(-10, 10)
        away_manager_point = random.randint(-10, 10)
        self.home_team.manager.influence_points.append(home_manager_point)
        self.away_team.manager.influence_points.append(away_manager_point)
        
        home_score = home_manager_point + sum(player.get_power() + random.randint(-3, 3) for player in self.home_team.get_roster())
        away_score = away_manager_point + sum(player.get_power() + random.randint(-3, 3) for player in self.away_team.get_roster())

        # Play additional periods if scores are equal
        while home_score == away_score:
            home_score = home_manager_point + sum(player.get_power() + random.randint(-3, 3) for player in self.home_team.get_roster())
            away_score = away_manager_point + sum(player.get_power() + random.randint(-3, 3) for player in self.away_team.get_roster())

        self.match_score = (home_score, away_score)
        self.update_players_performance()
        self.played = True

    def update_players_performance(self):
        periods_to_play = 4  # Adjust this number based on your requirements

        for player in self.home_team.get_roster() + self.away_team.get_roster():
            total_points = sum(player.get_power() + random.randint(-3, 3) for _ in range(periods_to_play))
            player.add_to_points(total_points)
            
    def update_managers_influence(self):
        self.home_team.get_manager().add_to_influence_detailed(self.match_score[0])
        self.away_team.get_manager().add_to_influence_detailed(self.match_score[1])

    def get_match_score(self):
        return self.match_score

    def get_teams(self):
        return self.home_team, self.away_team

    def get_home_team(self):
        return self.home_team

    def get_away_team(self):
        return self.away_team

    def get_winner(self):
        if self.played:
            return self.home_team if self.match_score[0] > self.match_score[1] else self.away_team
        return None

    def __str__(self):
        if self.played:
            return f"{self.home_team.get_name()} ({self.match_score[0]}) vs. ({self.match_score[1]}) {self.away_team.get_name()}"
        else:
            return f"{self.home_team.get_name()} vs. {self.away_team.get_name()}"

class Season:
    def __init__(self, teams_filename, managers_filename, players_filename):
        Manager.manager_counter = 0  
        self.teams = []
        self.managers = []
        self.players = []
        self.fixture = []
        self.current_week = 0
        self.load_players(players_filename)
        self.load_managers(managers_filename)
        self.load_teams(teams_filename)
        self.build_fixture()

    def load_players(self, players_filename):
        with open(players_filename, 'r') as file:
            player_names = [line.strip() for line in file.readlines()]
        self.players = [Player(name.split()[0], name.split(maxsplit=1)[1]) for name in player_names]

    def load_managers(self, managers_filename):
        with open(managers_filename, 'r') as file:
            manager_names = [line.strip().split() for line in file.readlines()]
        self.managers = [Manager(first_name, last_name) for first_name, last_name in manager_names]

    def load_teams(self, teams_filename):
        with open(teams_filename, 'r') as file:
            team_names = [line.strip() for line in file.readlines()]

        if not self.managers:
            print("Error: No managers available.")
            return

        for team_name in team_names:
            manager = random.choice(self.managers) 
            team_players = random.sample(self.players, 5) 
            team = Team(team_name, manager, team_players)
            self.teams.append(team)

        random.shuffle(self.teams)

    def reset(self):
        self.fixture = []
        self.current_week = 0
        self.build_fixture()

    def build_fixture(self):
        if self.fixture:
            self.reset()

        num_teams = len(self.teams)
        matches_per_week = num_teams // 2

        for week in range(6):
            week_matches = []

            for match in range(matches_per_week):
                team1 = self.teams[match]
                team2 = self.teams[(week + match) % (num_teams - 1)]
                week_matches.append(Match(team1, team2))

            self.fixture.append(week_matches)
    
    def get_week_fixture(self, week_no):
        if week_no <= 0 or week_no > len(self.fixture):
            return None
        return self.fixture[week_no - 1]

    def get_week_no(self):
        return self.current_week + 1
    
    def play_week(self):
        if self.current_week < len(self.fixture):
            for match in self.fixture[self.current_week]:
                match.play()
            self.current_week += 1

            self.players.sort(key=lambda x: x.get_points(), reverse=True)
            self.managers.sort(key=lambda x: x.get_influence(), reverse=True)
            self.teams.sort(key=lambda x: (x.get_wins(), x.get_total_score() - x.get_conceded()), reverse=True)


    def get_players(self):
        return self.players.copy()

    def get_managers(self):
        return self.managers.copy()

    def get_teams(self):
        return self.teams.copy()

    def get_season_length(self):
        return len(self.fixture)

    def get_best_player(self):
        return self.players[0] if self.players else None

    def get_best_manager(self):
        return self.managers[0] if self.managers else None

    def get_most_scoring_team(self):
        return self.teams[0] if self.teams else None

    def get_champion(self):
        if self.current_week == len(self.fixture):
            return self.teams[0] if self.teams else None
        else:
            return None


if __name__ == "__main__":
    teams_file = 'teams.txt'
    managers_file = 'managers.txt'
    players_file = 'players.txt'

    season21 = Season(teams_file, managers_file, players_file)

    # Play the matches
    for i in range(season21.get_season_length()):
        season21.play_week()

    # Display season statistics
    print("Champion is:", season21.get_champion())
    print("Most scoring team is:", season21.get_most_scoring_team())
    print("Best player is:", season21.get_best_player())
    print("Best manager is:", season21.get_best_manager())

    # Display all teams, their players, managers, and contributions
    print("\nTeam Details:")
    for team in season21.get_teams():
        print(f"\nTeam: {team}")
        print(f"Manager: {team.get_manager()}")
        print("Players:")
        for player in team.get_roster():
            print(f"  {player} - Power: {player.get_power()}, Points: {player.get_points()}")

    # Additional details if needed
    print("\nManager Details:")
    for manager in season21.get_managers():
        print(f"\nManager: {manager}")
        print(f"Influence Points: {manager.get_influence_detailed()}, Total Influence: {manager.get_influence()}")

    print("\nPlayer Details:")
    for player in season21.get_players():
        print(f"\nPlayer: {player}")
        print(f"Power: {player.get_power()}, Points: {player.get_points_detailed()}, Total Points: {player.get_points()}")

