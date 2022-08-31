#pragma once

#include "RegistrationHelper.hpp"
#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"

#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/BurstSliderGameNoteController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerGameNoteController.hpp"
#include "GlobalNamespace/SliderController.hpp"

namespace Lapiz::Objects::Beatmap {
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(BasicNoteRegistration, "normalBasicNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(BombNoteRegistration, "bombNotePrefab", GlobalNamespace::BombNoteController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(BurstSliderHeadNoteRegistration, "burstSliderHeadNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(BurstSliderNoteRegistration, "burstSliderNotePrefab", GlobalNamespace::BurstSliderGameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(ConnectedPlayerNoteRegistration, "multiplayerGameNoteControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerGameNoteController*, GlobalNamespace::MultiplayerConnectedPlayerGameNoteController*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(ProModeNoteRegistration, "proModeNotePrefab", GlobalNamespace::GameNoteController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LongSliderNoteRegistration, "sliderLongPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(MediumSliderNoteRegistration, "sliderMediumPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(ShortSliderNoteRegistration, "sliderShortPrefab", GlobalNamespace::SliderController*, GlobalNamespace::BeatmapObjectsInstaller*);
}