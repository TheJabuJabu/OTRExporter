/**
 * @file TextExporter.cpp
 * @brief Implements text resource export functionality for OTR format
 *
 * Handles the export of ZText resources into the binary OTR format, including:
 * - Message collections
 * - Text properties and formatting
 * - Control codes and special characters
 */

#include "TextExporter.h"
#include "../ZAPD/ZFile.h"
#include <fstream>

/**
 * @brief Exports a text resource to OTR binary format
 * 
 * Serializes a ZText resource into the standardized OTR binary format with:
 * 1. Standard OTR resource header with type and size
 * 2. Message count as uint32
 * 3. For each message:
 *    - Message ID (uint16) for lookup
 *    - Textbox type (uint8) for visual style
 *    - Textbox Y position (uint8) for screen placement
 *    - Full message string including control codes
 *
 * @param res The text resource to export (must be ZText*)
 * @param outPath Path where the OTR file will be written
 * @param writer Binary writer for serializing the data
 */
void OTRExporter_Text::Save(ZResource* res, const fs::path& outPath, BinaryWriter* writer)
{
	ZText* txt = (ZText*)res;

	WriteHeader(txt, outPath, writer, static_cast<uint32_t>(SOH::ResourceType::SOH_Text));

	writer->Write((uint32_t)txt->messages.size());

	for (size_t i = 0; i < txt->messages.size(); i++)
	{
		writer->Write(txt->messages[i].id);
		writer->Write(txt->messages[i].textboxType);
		writer->Write(txt->messages[i].textboxYPos);
		writer->Write(txt->messages[i].msg);

		printf("Message id: %d | Message: %s\n", txt->messages[i].id, txt->messages[i].msg.c_str());
	}


}
