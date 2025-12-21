#pragma once
#include "sampo/audio/sound_effect.hpp"

#include <miniaudio.h>

namespace Sampo
{
	enum class MASoundType
	{
		Invalid = 0,
		Raw,
		DataSource
	};

	struct MAAsyncLoadFinished
	{
		ma_async_notification_callbacks m_Callbacks;
		void* m_CallbackUserData;
	};

	class Win32SoundEffect : public SoundEffect
	{
	public:
		Win32SoundEffect(const std::string& aFilepath, const SoundEffectParams& aSoundEffectParams);
		virtual ~Win32SoundEffect();

		virtual bool Load() override;
		virtual bool Play() override;
		virtual bool Stop() override;

		virtual void SetIsLoaded() override;
		virtual float GetSoundEffectLength() const override;

		ma_resource_manager_data_source* GetSoundDataSource() { return &m_maDataSource;}
		const ma_sound_config& GetSoundInstanceConfig() const { return m_maSoundInstanceConfig; }
		const ma_resource_manager_data_source_config& GetDataResourceConfig() const { return m_maDataSourceConfig;}
	protected:

		void SetupSoundInstanceConfig();
		void SetupDataSourceSoundConfig();
		bool LoadDataSourceSound();

		uint32 GetLoadingFlags(MASoundType aSoundType) const;

		ma_sound m_maSoundEffect;
		ma_sound_config m_maSoundInstanceConfig{};
		ma_resource_manager_data_source m_maDataSource{};
		ma_resource_manager_data_source_config m_maDataSourceConfig{};

		MAAsyncLoadFinished m_loadFinished{};
		ma_resource_manager_pipeline_notifications m_maNotifications{};
	};
}