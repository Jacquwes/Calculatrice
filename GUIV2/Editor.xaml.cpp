//
// Editor.xaml.cpp
// Implementation of the Editor class
//

#include "pch.h"

#include "Editor.xaml.h"
#include "MainPage.xaml.h"
#include "FunctionEditor.xaml.h"

#include "AlgorithmUWP/Algorithm.h"
#include "EthyfierCalculatorWrapper/Ethyfier.h"
#include "EthyfierCalculatorWrapper/EthyfierCalculatorWrapper.h"

using namespace GUIV2;

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

Editor::Editor()
{
	InitializeComponent();
}

void GUIV2::Editor::navigationView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args)
{
	// Naviguer vers la calculatrice
	Frame->Navigate(Interop::TypeName(MainPage::typeid));
}

void GUIV2::Editor::saveButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Sauvegarder l'algorithme actuel
	saveAlgorithm(ref new UICommand());
}

void GUIV2::Editor::executeButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Exécute l'algorithme actuel
	std::string rawAlgorithm{};
	outputAlgorithm->Text = "";
	// Pour chaque fonction
	for (int i = 0; i < algorithmEditor->Children->Size; i++)
	{
		auto function = (FunctionEditor^)algorithmEditor->Children->GetAt(i);
		// Ajouter à l'algorithme la fonction
		rawAlgorithm += Utils::platformToStdString(function->getName()) + "\r" + Utils::platformToStdString(function->getInstructions()) + "\r";
	}
	try
	{
		// Fonction de sortie de l'algorithme
		std::function<void(std::string)> logFunction = [this](std::string message) -> void
		{
			outputAlgorithm->Text += Utils::stdToPlatformString(message);
		};
		// Exécuter l'algorithme
		Calculatrice::Algorithm::parseAlgorithm(rawAlgorithm, logFunction).execute();
	}
	catch (const Calculatrice::Utils::Error& e)
	{
		// Si une erreur est créée, l'afficher dans un dialogue
		Windows::UI::Popups::MessageDialog(Utils::stdToPlatformString(e.description), Utils::stdToPlatformString(e.name)).ShowAsync();
	}
}

void GUIV2::Editor::openButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Ouvrir un algorithme
	FileOpenPicker^ filePicker = ref new FileOpenPicker();
	filePicker->ViewMode = PickerViewMode::List;
	filePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	filePicker->FileTypeFilter->Clear();
	filePicker->FileTypeFilter->Append(".alg");

	IAsyncOperation<StorageFile^>^ pickFileOperation = filePicker->PickSingleFileAsync();
	auto pickFileTask = create_task(pickFileOperation);
	pickFileTask
		.then([](StorageFile^ file) { if (file) return FileIO::ReadBufferAsync(file); })
		.then([this](Streams::IBuffer^ fileBuffer)
			{
				// Supprimer l'algorithme déjà chargé dans le logiciel
				algorithmEditor->Children->Clear();
				// Lire le fichier choisi
				auto dataReader = Streams::DataReader::FromBuffer(fileBuffer);
				auto bufferArray = ref new Array<unsigned char, 1>(fileBuffer->Length);
				dataReader->ReadBytes(bufferArray);
				std::vector<int> data(bufferArray->begin(), bufferArray->end());
				// Lire le payload du fichier
				auto algorithm = Ethyfier::UWP::getFunctions(data);
				for (auto& i : algorithm)
				{
					// Et créer les fonctions correspondantes
					auto functionEditor = ref new FunctionEditor();
					functionEditor->setInstructions(ref new String(i.instructions.c_str()))->setName(ref new String(i.name.c_str()));
					algorithmEditor->Children->Append(functionEditor);
				}
		});
}

void GUIV2::Editor::documentationButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::System::Launcher::LaunchUriAsync(ref new Uri("https://github.com/JacqueSatan/Calculatrice/blob/master/AlgorithmUWP/specs.md"));
}

void GUIV2::Editor::addFunction_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Ajouter une fonction
	auto functionEditor = ref new FunctionEditor();
	algorithmEditor->Children->Append(functionEditor);
}

void GUIV2::Editor::closeAlgorithmFunctions(IUICommand^ command)
{
	algorithmEditor->Children->Clear();
}

void GUIV2::Editor::saveAlgorithm(IUICommand^ command)
{
	// Sauvegarder un algorithme
	FileSavePicker^ filePicker = ref new FileSavePicker();
	filePicker->DefaultFileExtension = ".alg";
	filePicker->SuggestedFileName = "programme";
	filePicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
	auto extension = ref new Platform::Collections::Vector<String^>();
	extension->Append(".alg");
	filePicker->FileTypeChoices->Insert("Algorithme", extension);

	IAsyncOperation<StorageFile^>^ pickFileOperation = filePicker->PickSaveFileAsync();
	auto pickFileTask = create_task(pickFileOperation);
	pickFileTask
		.then([this](task<StorageFile^> fileTask)
			{
					auto file = fileTask.get();
					if (file)
					{
						// Liste de fonctions
						std::vector<Ethyfier::variable> functions;
						// Pour chaque fonction de l'éditeur
						for (unsigned int i = 0; i < algorithmEditor->Children->Size; i++)
						{
							auto functionEditor = (FunctionEditor^)algorithmEditor->Children->GetAt(i);
							String^ name = functionEditor->getName();
							String^ instructions = functionEditor->getInstructions();
							// Ajoute la fonction à la liste
							functions.push_back({ Utils::platformToStdString(name), Utils::platformToStdString(instructions) });
						}

						// Sérialise l'algorithme
						std::vector<int> payload = Ethyfier::serialize(functions);
						// Convertit le vector en Array pour des raisons de compatibilités avec UWP
						auto arr = ref new Array<unsigned char>(static_cast<unsigned int>(payload.size()));
						for (int i = 0; i < payload.size(); i++)
							arr[i] = payload[i];

						// Ecrire dans le fichier
						return FileIO::WriteBytesAsync(file, arr);
					}
			})
		.then([command, this]() 
			{ 
				Windows::UI::Popups::MessageDialog("Algorithme sauvegardé.").ShowAsync();
				if (command->Label == "Oui")
					closeAlgorithmFunctions(ref new UICommand());
			});
}

void GUIV2::Editor::closeAlgorithm_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto dialog = ref new Windows::UI::Popups::MessageDialog("Voulez-vous enregistrer cet algorithme avant de le fermer ?");
	UICommand^ saveAlgorithmCommand = ref new UICommand(
		"Oui",
		ref new UICommandInvokedHandler(this, &Editor::saveAlgorithm));
	UICommand^ closeAlgorithmCommand = ref new UICommand(
		"Non",
		ref new UICommandInvokedHandler(this, &Editor::closeAlgorithmFunctions));
	UICommand^ cancelAlgorithmCommand = ref new UICommand(
		"Annuler");

	dialog->Commands->Append(saveAlgorithmCommand);
	dialog->Commands->Append(closeAlgorithmCommand);
	dialog->Commands->Append(cancelAlgorithmCommand);

	dialog->CancelCommandIndex = 2;
	dialog->DefaultCommandIndex = 0;

	dialog->ShowAsync();
}
