=================
How to Contribute
=================

We welcome community contributions to the Annotation and Image Markup(AIM) project.
Your contributions back to this repository will allow the broader
research community to benefit from your work and will allow your
enhancements to be integrated with those of others.  There are a few
guidelines that we ask contributors to follow so that we can have a
chance of keeping on top of things.

---------------
Getting Started
---------------

* Make sure you have a `GitHub Account`_.

* Fork the repository on GitHub to publish any proposed changes

* Submit a ticket for your issue at 
              * [AIM - Information Model(AIM)] (https://tracker.nci.nih.gov/browse/AIM)
              * [AIM - Enterprise Service(AIMES)] (https://tracker.nci.nih.gov/browse/AIMES)
              * [ AIM - Workstation (AIMWS)] (https://tracker.nci.nih.gov/browse/AIMWS)
  assuming one does not already exist.

  - Click on https://tracker.nci.nih.gov/secure/CreateIssue.jspa?pid=10002&issuetype=8 to get a jira account.
  - Clearly describe the issue including steps to reproduce when it is a bug.
  - Make sure you fill in the earliest version that you know has the issue.

.. _`GitHub Account`: https://github.com/signup/free

--------------
Making Changes
--------------

* Create a topic branch from where you want to base your work.

  - This is usually the master branch.
  - Only target release branches if you are certain your fix must be
    on that branch.
  - To quickly create a topic branch based on master::

     git checkout -b fix/master/my_contribution master

    Please avoid working directly on the master branch.

* Make commits of logical units.

* Please provide tests and documentation with your changes.

* Check for unnecessary whitespace with ``git diff --check`` before committing.

* Follow the `NCIP Good Practices for Commit Messages`_.
  Start with a one-line summary followed by a blank line followed by a
  detailed free-form description.

.. _`NCIP Good Practices for Commit Messages`: https://github.com/NCIP/ncip.github.com/wiki/Good-Practices#wiki-commit-messages

------------------
Submitting Changes
------------------

* In general, we require that the OSI-approved `BSD 3-Clause License`_
  be applied to code contributions.  There may be cases, however, that
  warrant the use of an alternate OSI-approved license and we will
  evaluate this situations case-by-case.

* Push your changes to a topic branch in your fork of the repository.

* Submit a pull request to the repository in the NCIP organization.

.. If the project uses an issue tracker, use the next bullet.
   Otherwise, remove the next bullet.  Delete this note either way.

* Update your 
* [AIM - Information Model(AIM)] (https://tracker.nci.nih.gov/browse/AIM)
* [AIM - Enterprise Service(AIMES)] (https://tracker.nci.nih.gov/browse/AIMES)
* [ AIM - Workstation (AIMWS)] (https://tracker.nci.nih.gov/browse/AIMWS) 
  ticket to mark that you have submitted code and are ready for it to be reviewed.

  - Include a link to the pull request in the ticket

.. _`BSD 3-Clause License`: http://opensource.org/licenses/BSD-3-Clause

--------------------
Additional Resources
--------------------

For help learning Git and Github, see the `NCIP Learning Resources`_.

.. _`NCIP Learning Resources`: https://github.com/NCIP/ncip.github.com/wiki/Learning-Resource
