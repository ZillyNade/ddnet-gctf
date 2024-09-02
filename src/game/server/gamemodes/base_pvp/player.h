#ifndef GAME_SERVER_GAMEMODES_BASE_PVP_PLAYER_H
// hack for headerguard linter
#endif

#ifndef IN_CLASS_PLAYER

#include <base/vmath.h>
#include <optional>
#include <vector>

// player object
class CPlayer
{
	std::optional<int> m_Score; // hack for IDEs
	int m_Team;
#endif // IN_CLASS_PLAYER

public:
	/*******************************************************************
	 * zCatch                                                          *
	 *******************************************************************/

	// Will be -1 when the player is alive
	int m_KillerId = -1;
	void SetTeamNoKill(int Team, bool DoChatMsg = false);
	void SetTeamRaw(int Team) { m_Team = Team; }
	// dead players can not respawn
	// will be used like m_RespawnDisabled in 0.7
	bool m_IsDead;
	bool m_GotRespawnInfo = false;
	std::vector<int> m_vVictimIds;

	/*******************************************************************
	 * gCTF                                                            *
	 *******************************************************************/
	bool m_GameStateBroadcast;
	int m_RespawnTick;
	bool m_IsReadyToEnter; // 0.7 ready change
	bool m_IsReadyToPlay; // 0.7 ready change
	bool m_DeadSpecMode; // 0.7 dead players

	/*******************************************************************
	 * shared                                                          *
	 *******************************************************************/
	// Will also be set if spree chat messages are turned off
	int m_Spree;
	//Anticamper
	bool m_SentCampMsg;
	int m_CampTick;
	vec2 m_CampPos;

	// kills, deaths and flag grabs/caps are tracked per round
	int m_Kills;
	int m_Deaths;
	int m_FlagCaptures;
	int m_FlagGrabs;

	void ResetStats()
	{
		m_Spree = 0;
		m_Kills = 0;
		m_Deaths = 0;
		m_FlagCaptures = 0;
		m_FlagGrabs = 0;
	}

	/*
		m_HasGhostCharInGame

		when the game starts for the first time
		and then a countdown starts there are no characters in game yet
		because they had no time to spawn

		but when the game reloads and tees were in game.
		those clients do not receive a new snap and still can see their tee.
		so their scoreboard is not forced on them.

		This variable marks those in game tees
	*/
	bool m_HasGhostCharInGame;
	int64_t m_LastReadyChangeTick;
	void IncrementScore() { AddScore(1); }
	void DecrementScore() { AddScore(-1); }
	void AddScore(int Score) { m_Score = m_Score.value_or(0) + Score; }

#ifndef IN_CLASS_PLAYER
}
#endif
