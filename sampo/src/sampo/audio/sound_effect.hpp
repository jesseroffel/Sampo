#pragma once

namespace Sampo
{
	struct SoundEffectParams
	{
		uint8 m_AdjustedVolume{ 100 };
		bool m_LoadImmediately{ false };
		bool m_AsyncLoad{ true };
		bool m_Looping{ false };
		bool m_StreamFile{false};
	};

	class SoundEffect
	{
	public:
		SoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams)
			: m_Filepath(aFilepath)
			, m_SoundEffectParams(aSoundEffectParams){}

		virtual ~SoundEffect() = default;

		virtual bool Load(bool aPlayImmediately = false) = 0;
		virtual bool Play() = 0;
		virtual void Stop() = 0;
		virtual bool Unload() = 0;

		virtual bool IsLoaded() const { return m_IsLoaded; }
		virtual void SetIsLoaded() { m_IsLoaded = true; }

		virtual bool IsOneOff() const { return m_IsOneOff;}
		virtual void SetIsOneOff() { m_IsOneOff = true; }

		virtual uint32 GetSoundEffectID() const {return m_SoundEffectID;}
		virtual const std::string& GetFilepath() const { return m_Filepath; }
		virtual float GetSoundEffectLength() const { return 0.f; }

		SoundEffectParams m_SoundEffectParams; // SAMPO_TODO: Make protected
		uint32 m_SoundEffectID{ 0u }; // SAMPO_TODO: Make protected UUID
	protected:

		std::string m_Filepath{};
		bool m_IsLoaded{ false };
		bool m_IsOneOff{ false };
	};
}