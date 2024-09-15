#ifndef GAME_SERVER_INSTAGIB_SQL_STATS_PLAYER_H
#define GAME_SERVER_INSTAGIB_SQL_STATS_PLAYER_H

#include <base/system.h>
#include <optional>

class CSqlStatsPlayer
{
public:
	// kills, deaths and flag grabs/caps are tracked per round
	int m_Kills;
	int m_Deaths;

	// Will also be set if spree chat messages are turned off
	// this is the spree highscore
	// the players current spree is in CPlayer::m_Spree
	int m_BestSpree;

	int m_FlagCaptures;
	int m_FlagGrabs;

	std::optional<float> m_FlagTime; // matching ddnet's m_BestTime
	// int m_FlaggerKills;

	void Reset()
	{
		m_Kills = 0;
		m_Deaths = 0;
		m_BestSpree = 0;
		m_FlagCaptures = 0;
		m_FlagGrabs = 0;
		m_FlagTime = std::nullopt;
	}

	void Merge(const CSqlStatsPlayer *pOther)
	{
		m_Kills += pOther->m_Kills;
		m_Deaths += pOther->m_Deaths;
		m_BestSpree = MergeIntHighest(pOther->m_BestSpree, m_BestSpree);
		m_FlagCaptures += pOther->m_FlagCaptures;
		m_FlagGrabs += pOther->m_FlagGrabs;
		m_FlagTime = MergeFloatOptionalLowest(pOther->m_FlagTime, m_FlagTime);
	}

	int MergeIntAdd(int Current, int Other) const
	{
		return Current + Other;
	}

	int MergeIntHighest(int Current, int Other) const
	{
		if(Current > Other)
			return Current;
		return Other;
	}

	int MergeIntLowest(int Current, int Other) const
	{
		if(Current < Other)
			return Current;
		return Other;
	}

	float MergeFloatHighest(float Current, float Other) const
	{
		if(Current > Other)
			return Current;
		return Other;
	}

	float MergeFloatLowest(float Current, float Other) const
	{
		if(Current < Other)
			return Current;
		return Other;
	}

	std::optional<float> MergeFloatOptionalLowest(std::optional<float> Current, std::optional<float> Other) const
	{
		if(Current.has_value() && !Other.has_value())
			return Current.value();
		if(!Current.has_value() && Other.has_value())
			return Other.value();
		if(!Current.has_value() && !Other.has_value())
			return std::nullopt;

		if(Current.value() < Other.value())
			return Current;
		return Other;
	}

	void Dump(const char *pSystem = "stats") const
	{
		dbg_msg(pSystem, "  kills: %d", m_Kills);
		dbg_msg(pSystem, "  deaths: %d", m_Deaths);
		dbg_msg(pSystem, "  spree: %d", m_BestSpree);
		dbg_msg(pSystem, "  flag_captures: %d", m_FlagCaptures);
		dbg_msg(pSystem, "  flag_grabs: %d", m_FlagGrabs);
		if(m_FlagTime.has_value())
			dbg_msg(pSystem, "  flag_time: %.2f", m_FlagTime.value());
		else
			dbg_msg(pSystem, "  flag_time: NULL");
	}

	bool HasValues() const
	{
		return m_Kills ||
		       m_Deaths ||
		       m_BestSpree ||
		       m_FlagCaptures ||
		       m_FlagGrabs ||
		       m_FlagTime.has_value();
	}

	CSqlStatsPlayer()
	{
		Reset();
	}
};

#endif
