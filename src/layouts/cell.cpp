#include "layouts/cell.h"
#include <stdexcept>

DECLARE_SOBJ(sad::layouts::Cell)

// ============================ PUBLIC METHODS ============================

sad::layouts::Cell::Cell() 
: m_row_span(1),
m_col_span(1), 
m_valign(sad::layouts::LVA_Middle), 
m_halign(sad::layouts::LHA_Middle),
m_stacking_type(sad::layouts::LST_Horizontal),
m_grid(NULL)
{
    
}

sad::layouts::Cell::~Cell()
{
    
}

void sad::layouts::Cell::toSerializable(sad::layouts::SerializableCell& cell) const
{
    cell.Width = m_width;
    cell.Height = m_height;
    cell.RowSpan = m_row_span;
    cell.ColSpan = m_col_span;
    cell.VAlign = m_valign;
    cell.HAlign = m_halign;
    cell.Children.clear();
    for(size_t i = 0; i < m_children.size(); i++)
    {
        cell.Children << m_children[i]->majorId();
    }
    cell.StackingType = m_stacking_type;
}

void sad::layouts::Cell::fromSerializable(
    sad::layouts::SerializableCell& cell,
    sad::db::Database* db
)
{
    this->m_width = cell.Width;
    this->m_height = cell.Height;
    this->m_row_span = cell.RowSpan;
    this->m_col_span = cell.ColSpan;
    this->m_valign = cell.VAlign;
    this->m_halign = cell.HAlign;
    for(size_t i = 0; i < m_children.size(); i++)
    {
        delete m_children[i];
    }
    this->m_children.clear();
    for(size_t i = 0; i < cell.Children.size(); i++)
    {
        sad::db::TypedLink<sad::SceneNode>* child = new sad::db::TypedLink<sad::SceneNode>();
        child->setDatabase(db);
        child->setMajorId(cell.Children[i]);
        this->m_children << child;
    }
    this->m_stacking_type = cell.StackingType;

    // TODO: Do not forget to notify a grid, after a serializable was loaded
    // Or grid should itself recompute stuff
}

// ============================ PRIVATE METHODS ============================

sad::layouts::Cell::Cell(const sad::layouts::Cell& o)
: m_row_span(o.m_row_span), 
m_col_span(o.m_col_span),
m_valign(o.m_valign),
m_halign(o.m_halign),
m_stacking_type(o.m_stacking_type),
m_grid(o.m_grid)
{
    throw std::runtime_error("Not implemented");
}

sad::layouts::Cell& sad::layouts::Cell::operator=(const sad::layouts::Cell& o)
{
    throw std::runtime_error("Not implemented");
    // ReSharper disable once CppUnreachableCode
    return *this;
}
