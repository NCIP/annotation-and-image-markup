/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/ofstd/oftest.h"
#include "dcmtk/dcmsr/dsrtree.h"


OFTEST(dcmsr_addTreeNode)
{
    DSRTree tree;
    /* first, create a simple tree of 6 nodes and check the references */
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode()), 1);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_belowCurrent), 2);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_afterCurrent), 3);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_afterCurrent), 4);
    OFCHECK_EQUAL(tree.gotoPrevious(), 3);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_belowCurrent), 5);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_afterCurrent), 6);
    OFCHECK_EQUAL(tree.gotoPrevious(), 5);
    OFCHECK_EQUAL(tree.goUp(), 3);
    OFCHECK_EQUAL(tree.gotoPrevious(), 2);
    OFCHECK_EQUAL(tree.goUp(), 1);
    /* then, insert new nodes into the tree and check the references */
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_belowCurrent), 7);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_beforeCurrent), 8);
    OFCHECK_EQUAL(tree.gotoNext(), 7);
    OFCHECK_EQUAL(tree.addNode(new DSRTreeNode(), DSRTypes::AM_beforeCurrent), 9);
    OFCHECK_EQUAL(tree.gotoPrevious(), 8);
    OFCHECK_EQUAL(tree.goUp(), 1);
    /* and finally, iterate over all tree nodes ... */
    OFCHECK_EQUAL(tree.getLevel(), 1);
    OFCHECK_EQUAL(tree.iterate(), 2);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 3);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 5);
    OFCHECK_EQUAL(tree.getLevel(), 3);
    OFCHECK_EQUAL(tree.iterate(), 6);
    OFCHECK_EQUAL(tree.getLevel(), 3);
    OFCHECK_EQUAL(tree.iterate(), 4);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 8);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 9);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 7);
    OFCHECK_EQUAL(tree.getLevel(), 2);
    OFCHECK_EQUAL(tree.iterate(), 0);
}
