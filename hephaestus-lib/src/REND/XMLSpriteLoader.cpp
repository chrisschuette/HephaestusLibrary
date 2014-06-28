/* 
 * File:   XMLSpriteLoader.cpp
 * Author: chris
 * 
 * Created on June 18, 2014, 11:36 AM
 */

#include "XMLSpriteLoader.h"
#include "../ERR/ERR.h"
#include "../DMGD/Resource.h"
#include "../FSVR/ResourceMetaData.h"
#include "../GL/Sprite.h"
#include "../GL/GradientSprite.h"
#include "../GL/AnimatedSprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "../LOG/Core.h"
#include <rapidxml.hpp>

#define NAME "XMLSpriteLoader"

namespace REND {

    XMLSpriteLoader::XMLSpriteLoader(TextureManager& textureMgr, ShaderManager& shaderMgr)
    : DMGD::Loader<REND::Sprite>()
    // , m_spriteDescription(0)
    , m_textureMgr(textureMgr)
    , m_shaderMgr(shaderMgr)
    , m_XML(0) {
    }

    XMLSpriteLoader::~XMLSpriteLoader() {
        if (m_XML)
            delete [] m_XML;
    }

    void XMLSpriteLoader::onLoadComplete(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        DMGD::Resource<REND::Sprite>& res = static_cast<DMGD::Resource<REND::Sprite>&> (resource);

        if (m_XML)
            delete [] m_XML;

        // 0-terminate XML
        m_XML = new char[getRawDataSize() + 1];
        memcpy(m_XML, getRawData(), getRawDataSize());
        m_XML[getRawDataSize()] = 0;

        // free raw data
        discardRawData();

        // decide about instantiation
        FSVR::Loader::onLoadComplete(resource, metadata);
    }

    REND::Sprite* XMLSpriteLoader::createSprite(const FSVR::ResourceMetaData& metadata) {
        using namespace rapidxml;
        xml_document<> doc;
        doc.parse < 0 > (m_XML);

        //determine resource name
        xml_node<> *nameNode = doc.first_node("name");
        if (!nameNode)
            THROWS("No name set.");
        if (std::string(nameNode->value()) != metadata.getResourceID())
            THROWS("name and RID do not coincide.");

        // determine texture RID
        xml_node<> *textureNode = doc.first_node("texture");
        if (!textureNode)
            THROWS("No texture set.");
        std::string textureRID = textureNode->value();

        // determine shader name
        xml_node<> *shaderNode = doc.first_node("shader");
        if (!shaderNode)
            THROWS("No shader set.");
        std::string shaderName = shaderNode->value();
        return new GL::Sprite(m_textureMgr.getResourceHandle(textureRID), m_shaderMgr.getShaderProgramInstance(shaderName));
    }

    REND::Sprite* XMLSpriteLoader::createGradientSprite(const FSVR::ResourceMetaData& metadata) {
        using namespace rapidxml;
        xml_document<> doc;
        doc.parse < 0 > (m_XML);

        //determine resource name
        xml_node<> *nameNode = doc.first_node("name");
        if (!nameNode)
            THROWS("No name set.");
        if (std::string(nameNode->value()) != metadata.getResourceID())
            THROWS("name and RID do not coincide.");

        //determine texture resource ID
        xml_node<> *textureNode = doc.first_node("texture");
        if (!textureNode)
            THROWS("No texture set.");
        std::string textureRID = textureNode->value();

        // determine shader name
        xml_node<> *shaderNode = doc.first_node("shader");
        if (!shaderNode)
            THROWS("No shader set.");
        std::string shaderName = shaderNode->value();

        xml_node<> *stopsNode = doc.first_node("stops");
        if (!stopsNode)
            THROWS("No stops set.");
        std::vector<GradientStop> stops;
        for (xml_node<> *stopNode = stopsNode->first_node();
                stopNode; stopNode = stopNode->next_sibling()) {
            if (strcmp(stopNode->name(), "stop") != 0)
                THROWS("Invalid stop");
            xml_attribute<>* positionAtt = stopNode->first_attribute("position");
            xml_attribute<>* colorAtt = stopNode->first_attribute("color");
            if (!positionAtt || !colorAtt)
                THROWS("Invalid stop node.");

            float position = atof(positionAtt->value());

            MATH::vec4 color;
            char comma = ',';
            const char* p = colorAtt->value();
            const char * pos;
            int n = 0;
            while ((pos = strchr(p, comma)) != 0) {
                color.data[n] = (float) atoi(std::string(p, pos).c_str()) / 255.f;
                p = pos + 1;
                n++;
            }
            color.data[n] = atof(p);

            GradientStop stop;
            stop.color = color;
            stop.position = position;
            stops.push_back(stop);
        }

        GL::GradientSprite* sprite = new GL::GradientSprite(m_textureMgr.getResourceHandle(textureRID), m_shaderMgr.getShaderProgramInstance(shaderName));
        for (std::vector<GradientStop>::const_iterator i = stops.begin(), e = stops.end(); i != e; ++i) {
            const GradientStop& stop = (*i);
            L(normal) << "Adding stop with position " << stop.position << " color " << stop.color.r << " "
                    << stop.color.g << " " << stop.color.b << " " << stop.color.a;
            sprite->addStop(stop.position, stop.color);
        }
        return sprite;
    }

    REND::Sprite* XMLSpriteLoader::createAnimatedSprite(const FSVR::ResourceMetaData& metadata) {
        //parse XML
        using namespace rapidxml;
        xml_document<> doc;
        doc.parse < 0 > (m_XML);

        //determine resource name
        xml_node<> *nameNode = doc.first_node("name");
        if (!nameNode)
            THROWS("No name set.");
        if (std::string(nameNode->value()) != metadata.getResourceID())
            THROWS("name and RID do not coincide.");

        //determine texture resource ID
        xml_node<> *textureNode = doc.first_node("texture");
        if (!textureNode)
            THROWS("No texture set.");
        std::string textureRID = textureNode->value();

        // determine shader name
        xml_node<> *shaderNode = doc.first_node("shader");
        if (!shaderNode)
            THROWS("No shader set.");
        std::string shaderName = shaderNode->value();


        xml_node<> *atlasNode = doc.first_node("atlas");
        if (!atlasNode)
            THROWS("No frame defined");
        xml_attribute<>* frameWidthAtt = atlasNode->first_attribute("width");
        xml_attribute<>* frameHeightAtt = atlasNode->first_attribute("height");
        
        // get frame dimensions
        MATH::ivec2 frameDimensions;
        frameDimensions.x = atoi(frameWidthAtt->value());
        frameDimensions.y = atoi(frameHeightAtt->value());

        // create a GL::AnimatedSprite
        GL::AnimatedSprite* animatedSprite = new GL::AnimatedSprite(m_textureMgr.getResourceHandle(textureRID), m_shaderMgr.getShaderProgramInstance(shaderName), frameDimensions);

        // read in the frame definitions
        for (xml_node<> *frameNode = atlasNode->first_node();
                frameNode; frameNode = frameNode->next_sibling()) {
            // make sure this really is a frame node
            if (strcmp(frameNode->name(), "frame") != 0)
                THROWS("Invalid frame.");
            xml_attribute<>* nameAtt = frameNode->first_attribute("name");
            xml_attribute<>* XAtt = frameNode->first_attribute("x");
            xml_attribute<>* YAtt = frameNode->first_attribute("y");
            if (!nameAtt || !XAtt || !YAtt)
                THROWS("Invalid frame.");
            std::string frameName = nameAtt->value();
            int frameX = atoi(XAtt->value());
            int frameY = atoi(YAtt->value());

            GL::AnimatedSprite::Frame frame;
            frame.name = frameName;
            frame.x = frameX;
            frame.y = frameY;

            L(normal) << "Added frame name=" << frame.name << " x=" << frame.x << " y=" << frame.y;

            animatedSprite->addFrame(frame);
        }

        // read in all the animations
        for (xml_node<> *animationNode = doc.first_node("animation");
                animationNode; animationNode = animationNode->next_sibling("animation")) {

            // determine properties of the animation
            xml_attribute<>* nameAtt = animationNode->first_attribute("name");
            xml_attribute<>* tpfAtt = animationNode->first_attribute("tpf");
            xml_attribute<>* flippedHAtt = animationNode->first_attribute("flippedH");
            xml_attribute<>* flippedVAtt = animationNode->first_attribute("flippedV");

            if (!nameAtt || !tpfAtt || !flippedHAtt || !flippedVAtt)
                THROWS("Invalid animation.");

            std::string animationName = nameAtt->value();

            int tpf = atoi(tpfAtt->value());

            bool flippedH;
            if (std::string(flippedHAtt->value()) == "true")
                flippedH = true;
            else if (std::string(flippedHAtt->value()) == "false")
                flippedH = false;
            else
                THROWS("Unknown value for flippedH.");

            bool flippedV;
            if (std::string(flippedVAtt->value()) == "true")
                flippedV = true;
            else if (std::string(flippedVAtt->value()) == "false")
                flippedV = false;
            else
                THROWS("Unknown value for flippedV.");

            // go over the frames
            std::vector<std::string> frameNames;
            for (xml_node<> *frameNode = animationNode->first_node();
                    frameNode; frameNode = frameNode->next_sibling()) {
                // make sure this really is a frame node
                if (strcmp(frameNode->name(), "frame") != 0)
                    THROWS("Invalid frame.");
                xml_attribute<>* frameNameAtt = frameNode->first_attribute("name");
                if (!frameNameAtt)
                    THROWS("Invalid frame.");
                std::string frameName = frameNameAtt->value();
                frameNames.push_back(frameName);
            }

            L(normal) << "Added animation name=" << animationName << " tpf=" << tpf << " flippedH=" << (flippedH ? "true" : "false") << " flippedV=" << (flippedV ? "true" : "false");

            animatedSprite->addAnimation(animationName, frameNames, tpf, flippedH, flippedV);
        }

        return animatedSprite;
    }

    void XMLSpriteLoader::instantiate(FSVR::Resource& resource, const FSVR::ResourceMetaData& metadata) {
        if (!m_XML)
            THROWS("No XML available.");

        REND::Sprite* sprite = 0;

        // read out metadata and create payload class
        if (metadata.getType() == "sprite")
            sprite = createSprite(metadata);
        else if (metadata.getType() == "gradientsprite")
            sprite = createGradientSprite(metadata);
        else if (metadata.getType() == "animatedsprite")
            sprite = createAnimatedSprite(metadata);
        else
            THROWS("Resource is not a a sprite: type = " + metadata.getType());

        // discard XML data
        if (m_XML)
            delete [] m_XML;
        m_XML = 0;

        // set sprite in resource
        DMGD::Resource<REND::Sprite>& res = static_cast<DMGD::Resource<REND::Sprite>&> (resource);
        res.setInstance(sprite);

        // mark as active
        FSVR::Loader::instantiate(resource, metadata);
    }
}
