#pragma once

#include "RegistrationHelper.hpp"
#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"

#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/BurstSliderGameNoteController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerGameNoteController.hpp"
#include "GlobalNamespace/SliderController.hpp"

namespace Lapiz::Objects::Beatmap {
    using BasicNoteRegistration = ::Lapiz::Objects::Registration<"normalBasicNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using BombNoteRegistration = ::Lapiz::Objects::Registration<"bombNotePrefab", GlobalNamespace::BombNoteController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using BurstSliderHeadNoteRegistration = ::Lapiz::Objects::Registration<"burstSliderHeadNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using BurstSliderNoteRegistration = ::Lapiz::Objects::Registration<"burstSliderNotePrefab", GlobalNamespace::BurstSliderGameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using ConnectedPlayerNoteRegistration = ::Lapiz::Objects::Registration<"multiplayerGameNoteControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerGameNoteController*, GlobalNamespace::MultiplayerConnectedPlayerGameNoteController*>;
    using ProModeNoteRegistration = ::Lapiz::Objects::Registration<"proModeNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using LongSliderNoteRegistration = ::Lapiz::Objects::Registration<"sliderLongPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using MediumSliderNoteRegistration = ::Lapiz::Objects::Registration<"sliderMediumPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*>;
    using ShortSliderNoteRegistration = ::Lapiz::Objects::Registration<"sliderShortPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*>;
}

DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::BasicNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::BombNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::BurstSliderHeadNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::BurstSliderNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::ConnectedPlayerNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::ProModeNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::LongSliderNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::MediumSliderNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Beatmap::ShortSliderNoteRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
