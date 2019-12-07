#include "Topology.h"

Topology::Topology(D3DGFX& gfx, D3D11_PRIMITIVE_TOPOLOGY topol)
	: Bindable(gfx)
	, topology(topol)
{
}

void Topology::bind()
{
	get_device_context()->IASetPrimitiveTopology(topology);
}
