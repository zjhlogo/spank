/*!
 * \file ModelViewApp.h
 * \date 10-21-2014 10:39:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#include <BaseApp.h>

class ModelViewApp : public BaseApp
{
public:
	ModelViewApp();
	virtual ~ModelViewApp();

	virtual bool initialize() override;
	virtual void terminate() override;

protected:
	virtual void update(float dt) override;
	virtual void render() override;

private:
	spank::MeshData* m_pMeshData{ nullptr };

	float m_rot{ 0.0f };

};
