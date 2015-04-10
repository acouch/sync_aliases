## Drush Sync Aliases
Searches file system for drush alias files and symlinks them to your local .drush folder so you can use them.

This facilitates distributing drush alias files by project. Drush alias files are stored in a directory like ``assets/drush/example_project.aliases.drushrc.php``.

After running ``drush alias-sync`` the following symlink is created:

```
/home/my_user_name/.drush/example_project.aliases.drushrc.php -> /var/www/example_project/`assets/drush/example_project.aliases.drushrc.php
```
### Why?
Alternatives to this are sharing drush alias files via service like Drush Fetcher or Pantheon's terminus.

This system allows us to grant access to drush aliases by project.
